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
				const int instancingCount = geo.geometry->getInstancingCount();
				const int vertexSize = geo.geometry->getGeoInfo().vertex.size();
				const int indexSize = geo.geometry->getIndexSize();

				GLGEOMETRY_CAST(geo.geometry)->getBuffer()->bind();
				basicLightShader->setMat4("transform", transform.transform.get());
				basicLightShader->setVec3(material.interop.color_name, material.interop.color);
				basicLightShader->setVec3(material.interop.lightColor_name, material.interop.lightColor);
				basicLightShader->setVec3(material.interop.lightPos_name, material.interop.lightPos);

				basicLightShader->setVec3(cameraInterop.eyeWorldPosition_name, cameraInterop.eyeWorldPosition);

				basicLightShader->setMat4(cameraInterop.proj_name, cameraInterop.proj);
				basicLightShader->setMat4(cameraInterop.view_name, cameraInterop.view);

				if(geo.geometry->getIndexSize() != 0)
				{
					GLCHECK(glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0));
				}
				else 
				{
					GLCHECK(glDrawArrays(GL_TRIANGLES, 0, vertexSize));
				}

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

	auto& instancingShader = g_shaders[BasicLightInstancingMaterial::name];
	{
		assert(instancingShader != nullptr);
		instancingShader->use();
		registry.view<BasicLightInstancingMaterial, UpdateState, GeometryComponent>().each(
			[&cameraInterop, &instancingShader](const entt::entity& entity, BasicLightInstancingMaterial& material,
												UpdateState& state, GeometryComponent& geo)
			{
				const int instancingCount = geo.geometry->getInstancingCount();
				const int vertexSize = geo.geometry->getGeoInfo().vertex.size();
				const int indexSize = geo.geometry->getIndexSize();


				if(material.interop.bIsDirty)
				{
					auto& transform = material.interop.transform;
					auto& color = material.interop.color;
					geo.geometry->updateInstancingBuffer(0, transform.size()*sizeof(ns::Mat4), transform.data());
					geo.geometry->updateInstancingBuffer(1, color.size()*sizeof(ns::Vec4), color.data());
					material.interop.bIsDirty = false;
				}

				GLGEOMETRY_CAST(geo.geometry)->getBuffer()->bind();

				instancingShader->setMat4(cameraInterop.proj_name, cameraInterop.proj);
				instancingShader->setMat4(cameraInterop.view_name, cameraInterop.view);

				instancingShader->setVec3(material.interop.lightColor_name, material.interop.lightColor);
				instancingShader->setVec3(material.interop.lightPos_name, material.interop.lightPos);
				instancingShader->setVec3(cameraInterop.eyeWorldPosition_name, cameraInterop.eyeWorldPosition);

				if(geo.geometry->getIndexSize() != 0)
				{
					GLCHECK(glDrawElementsInstanced(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0, instancingCount));
				}
				else 
				{
					GLCHECK(glDrawArraysInstanced(GL_TRIANGLES, 0, 36, instancingCount));
				}

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