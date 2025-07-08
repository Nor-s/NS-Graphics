#include "glRenderer.h"
#include "glRenderTarget.h"
#include "glShader.h"
#include "../../scene/nsScene.h"

namespace ns
{
GlRenderer::GlRenderer()
{
}

void GlRenderer::bind()
{
   	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, sceneRenderTarget_->getFbo()));
	auto rect = sceneRenderTarget_->getViewport();
	GLCHECK(glViewport(rect.x, rect.y, rect.w, rect.h));
	GLCHECK(glClearColor(0.1f, 0.2f, 0.1f, 1.0f));
	GLCHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void GlRenderer::unbind()
{
	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

uint32_t GlRenderer::getRenderTargetId()
{
	return sceneRenderTarget_->getFbo();
}

uint64_t GlRenderer::getColorTexture()
{
	return sceneRenderTarget_->getColorTexture();
}

Resolution GlRenderer::getResolution() const
{
	return Resolution();
}

void GlRenderer::render(Scene* scene)
{
	bind();

	scene->draw();

	auto& registry = scene->getRegistry();

	// registry.view<ActiveEntity, GeometryComponent, TransformComponent>();


	unbind();
}

void GlRenderer::onResize(const Resolution& res)
{
 	sceneRenderTarget_.reset();
	sceneRenderTarget_ = ns::GlRenderTarget::gen(ns::GlRenderTarget::Spec{
		.colorFormat = {ns::ColorFormat::RGBA8}, .depthFormat = ns::DepthFormat::DEPTH24_STENCIL8, .resolution = res});   
}

}	 // namespace ns