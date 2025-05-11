#ifndef _NS_GRAPHICS_CORE_GPU_GL_RENDER_TARGET_H_
#define _NS_GRAPHICS_CORE_GPU_GL_RENDER_TARGET_H_

#include "glCommon.h"

namespace ns
{

class GlRenderTarget
{
public:
	struct Spec
	{
		Resolution resolution{};
		std::vector<ColorFormat> colorFormat{};
		DepthFormat depthFormat = DepthFormat::NONE;
	};

	static std::unique_ptr<GlRenderTarget> gen(const Spec& spec, GLuint beforeFbo = 0);

public:
	~GlRenderTarget();
	GLuint getFbo()
	{
		return fbo_;
	}
	GLuint getColorTexture(int index = 0)
	{
		return colorTexture_[index];
	}

	Resolution& getresolution()
	{
		return resolution_;
	}
	void setViewport(const Rect viewportRect)
	{
		viewportRect_ = viewportRect;
	}
	const Rect& getViewport()
	{
		return viewportRect_;
	}

protected:
	friend std::unique_ptr<GlRenderTarget> std::make_unique<GlRenderTarget>();
	GlRenderTarget() = default;
	void init(const Spec& spec, GLuint beforeFbo = 0);
	void deinit();

private:
	Resolution resolution_{};
	Rect viewportRect_{};
	GLuint fbo_ = 0;
	std::vector<GLuint> colorTexture_{};
	GLuint depthStencilBuffer_ = 0;
};

}	 // namespace ns

#endif