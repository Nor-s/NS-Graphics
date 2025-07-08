#include "glRenderer.h"
#include "glRenderTarget.h"
#include "glShader.h"
#include "../../scene/nsScene.h"
#include "glGeometry.h"
#include "../../entity/component/components.h"

#define GLGEOMETRY_CAST(geo) static_cast<ns::GlGeometry*>(geo.get())

namespace ns
{
GlRenderer::GlRenderer()
{
}

void GlRenderer::bind()
{
	GLCHECK(glEnable(GL_DEPTH_TEST));
	GLCHECK(glBindFramebuffer(GL_FRAMEBUFFER, sceneRenderTarget_->getFbo()));
	auto rect = sceneRenderTarget_->getViewport();
	GLCHECK(glViewport(rect.x, rect.y, rect.w, rect.h));
	GLCHECK(glClearColor(1.0f, 0.2f, 0.1f, 1.0f));
	GLCHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
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
	auto& registry = scene->getRegistry();
	auto* camera = scene->getMainCamera();

	if (camera == nullptr)
		return;
	auto cameraInterop = camera->getCameraInterop();

	bind();

	scene->draw();

	auto& basicLightShader = g_shaders[BasicLightMaterial::name];
	{
		assert(basicLightShader != nullptr);
		basicLightShader->use();

		registry.view<BasicLightMaterial, UpdateState, GeometryComponent, TransformComponent>().each(
			[&cameraInterop, &basicLightShader](const entt::entity& entity, BasicLightMaterial& material,
												UpdateState& state, GeometryComponent& geo,
												TransformComponent& transform)
			{
				GLGEOMETRY_CAST(geo.geometry)->getBuffer()->bind();
				basicLightShader->setMat4("transform", transform.transform.get());
				basicLightShader->setVec3(material.interop.color_name, material.interop.color);
				basicLightShader->setVec3(material.interop.lightColor_name, material.interop.lightColor);
				basicLightShader->setVec3(material.interop.lightPos_name, material.interop.lightPos);

				basicLightShader->setVec3(cameraInterop.eyeWorldPosition_name, cameraInterop.eyeWorldPosition);

				basicLightShader->setMat4(cameraInterop.proj_name, cameraInterop.proj);
				basicLightShader->setMat4(cameraInterop.view_name, cameraInterop.view);

				glDrawElements(GL_TRIANGLES, geo.geometry->getIndexSize(), GL_UNSIGNED_INT, 0);

				GLGEOMETRY_CAST(geo.geometry)->getBuffer()->unbind();
			});
	}

	auto& solidColorShader = g_shaders[SolidColorMaterial::name];
	{
		assert(solidColorShader != nullptr);
		solidColorShader->use();
		registry.view<SolidColorMaterial, UpdateState, GeometryComponent, TransformComponent>().each(
			[&cameraInterop, &solidColorShader](const entt::entity& entity, SolidColorMaterial& material,
												UpdateState& state, GeometryComponent& geo,
												TransformComponent& transform)
			{
				GLGEOMETRY_CAST(geo.geometry)->getBuffer()->bind();
				solidColorShader->setMat4("transform", transform.transform.get());
				solidColorShader->setVec3(material.interop.color_name, material.interop.color);
				solidColorShader->setMat4(cameraInterop.proj_name, cameraInterop.proj);
				solidColorShader->setMat4(cameraInterop.view_name, cameraInterop.view);

				glDrawElements(GL_TRIANGLES, geo.geometry->getIndexSize(), GL_UNSIGNED_INT, 0);

				GLGEOMETRY_CAST(geo.geometry)->getBuffer()->unbind();
			});
	}

	unbind();
}

void GlRenderer::onResize(const Resolution& res)
{
	sceneRenderTarget_.reset();
	sceneRenderTarget_ = ns::GlRenderTarget::gen(ns::GlRenderTarget::Spec{
		.colorFormat = {ns::ColorFormat::RGBA8}, .depthFormat = ns::DepthFormat::DEPTH24_STENCIL8, .resolution = res});

	// TODO: move init shader call
	initShader();
}

}	 // namespace ns