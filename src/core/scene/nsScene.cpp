#include "nsScene.h"


namespace ns
{

Scene::Scene()
{
}

void Scene::init(const Resolution& res)
{
  sceneRenderTarget_ = ns::GlRenderTarget::gen(
		ns::GlRenderTarget::Spec{
			.colorFormat = {ns::ColorFormat::RGBA8},
			.depthFormat = ns::DepthFormat::DEPTH24_STENCIL8,
			.resolution = res
		}
	);
}

void Scene::draw(const SystemIO& io)
{
	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, sceneRenderTarget_->getFbo()));
	auto rect = sceneRenderTarget_->getViewport();
	GLCHECK(glViewport(rect.x, rect.y, rect.w, rect.h));
	GLCHECK(glClearColor(1.0f, 1.0, 0, 1.0f));
	GLCHECK(glClear(GL_COLOR_BUFFER_BIT));
    
	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

uint64_t Scene::getSceneImage()
{
	return sceneRenderTarget_->getColorTexture();
}

Resolution Scene::getResolution()
{
    return sceneRenderTarget_->getresolution();
}

}	 // namespace ns