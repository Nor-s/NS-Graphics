#include "glRenderTarget.h"

#include "glCommon.h"

namespace ns
{
GLenum ConvertFormat(ns::DepthFormat format)
{
	return GL_DEPTH24_STENCIL8;
}
GLenum ConvertFormat(ns::ColorFormat format)
{
	switch (format)
	{
		case ns::ColorFormat::RGBA8:
			return GL_RGBA;
		case ns::ColorFormat::R32:
			return GL_RED_INTEGER;
		default:
			return GL_RGBA;
	}
}
GLenum ConvertInternalFormat(ns::ColorFormat format)
{
	switch (format)
	{
		case ns::ColorFormat::RGBA8:
			return GL_RGBA8;
		case ns::ColorFormat::R32:
			return GL_R32I;
		default:
			return GL_RGBA8;
	}
}
GLenum GetDataType(ns::ColorFormat format)
{
	switch (format)
	{
		case ns::ColorFormat::R32:
			return GL_INT;
		default:
			return GL_UNSIGNED_BYTE;
	}
}
void SetTexParameteri(ns::ColorFormat format)
{
	switch (format)
	{
		case ns::ColorFormat::R32:
			GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			break;
		default:
			GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			break;
	}
}

void AttachColorAttachment(GLuint& colorTexture, Resolution resolution, ColorFormat colorFormat, int index)
{
	GLenum format = ConvertFormat(colorFormat);
	GLenum internalFormat = ConvertInternalFormat(colorFormat);
	GLenum textureTarget = GL_TEXTURE_2D;
	GLenum dataType = GetDataType(colorFormat);

	GLCHECK(glGenTextures(1, &colorTexture));
	GLCHECK(glBindTexture(textureTarget, colorTexture));

	GLCHECK(SetTexParameteri(colorFormat));
	GLCHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, resolution.width, resolution.height, 0, format, dataType,
						 nullptr));
	GLCHECK(glBindTexture(textureTarget, 0));
	GLCHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget, colorTexture, 0));
}

void AttachDepthRBO(GLuint& depthBuffer, Resolution resolution, DepthFormat depthFormat)
{
	GLenum format = ConvertFormat(depthFormat);

	GLCHECK(glGenRenderbuffers(1, &depthBuffer));
	GLCHECK(glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer));

	GLCHECK(glRenderbufferStorage(GL_RENDERBUFFER, format, resolution.width, resolution.height));

	GLCHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	GLCHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer));
}

std::unique_ptr<GlRenderTarget> GlRenderTarget::gen(const Spec& spec, GLuint beforeFbo)
{
	auto& resolution = spec.resolution;
	auto target = std::make_unique<GlRenderTarget>();
	target->init(spec, beforeFbo);
	return target;
}

GlRenderTarget::~GlRenderTarget()
{
	deinit();
}

void GlRenderTarget::init(const Spec& spec, GLuint beforeFbo)
{
	if (fbo_ != 0)
	{
		deinit();
	}
	resolution_ = spec.resolution;

	// gen buffer
	GLCHECK(glGenFramebuffers(1, &fbo_));
	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo_));

	// Attach Color Texture
	int size = (spec.colorFormat.size() > 0) ? spec.colorFormat.size() : 1;
	colorTexture_.resize(size);
	std::vector<GLenum> drawBuffers;
	for (int i = 0; i < size; i++)
	{
		auto format = (spec.colorFormat.size() > i) ? spec.colorFormat[i] : ColorFormat::RGBA8;
		colorTexture_.push_back(0);
		AttachColorAttachment(colorTexture_[i], resolution_, format, i);
		drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
	}
	GLCHECK(glDrawBuffers(drawBuffers.size(), drawBuffers.data()));

	// Attach Depth Buffer
	if (spec.depthFormat != DepthFormat::NONE)
	{
		AttachDepthRBO(depthStencilBuffer_, resolution_, spec.depthFormat);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		NS_CRITICAL("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}

	// set viewport
	setViewport({0, 0, resolution_.width, resolution_.height});

	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, beforeFbo));
}

void GlRenderTarget::deinit()
{   
	if(fbo_ != 0)
	{
		GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GLCHECK(glDeleteFramebuffers(1, &fbo_));
		fbo_ = 0;
	}
	else return;

	if(colorTexture_.size() > 0)
	{
		GLCHECK(glDeleteTextures(colorTexture_.size(), colorTexture_.data()));
		colorTexture_.clear();
	}
	if(depthStencilBuffer_ != 0)
	{
		GLCHECK(glDeleteRenderbuffers(1, &depthStencilBuffer_));
		depthStencilBuffer_ = 0;
	}
}

}	 // namespace ns