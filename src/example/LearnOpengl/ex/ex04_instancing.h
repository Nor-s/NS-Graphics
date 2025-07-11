#ifndef _LEARN_GL_EX_04_INSTANCING_H_
#define _LEARN_GL_EX_04_INSTANCING_H_

#include <core/gpu/gl/glGeometry.h>
#include "example.h"
#include <core/entity/component/components.h>
#include <core/scene/nsScene.h>
#include "shader/shaders.h"

#define GLGEOMETRY_CAST(geo) static_cast<ns::GlGeometry*>(geo.get())

/**
https://learnopengl.com/Advanced-OpenGL/Instancing


 */
class Ex04_Instancing : public Example
{
public:
	const std::string& toString() override
	{
		static const std::string ret = "ex04 Instancing";
		return ret;
	}
	~Ex04_Instancing()
	{
		destroy();
	}
	void destroy()
	{
	}
	void content() override
	{
		instancingShader_.init(Shaders::basicLighInstancingtVert, Shaders::basicLightFrag);
		lightShader_.init(Shaders::basicVert, Shaders::solidColorFrag);

		auto res = ns::editor::App::GetAppContext().res;
		scene_.init(res);

		// camera
		cameraEntity_ =  ns::Scene::CreateEntity(&scene_, "camera");
		camera_ = &cameraEntity_.addComponent<ns::CameraComponent>().camera;
		camera_->transform.position = {1000.0f, 1000.0f ,1000.0f};
		camera_->setRes(res);
		camera_->setPerspective();

		transforms_.resize(instancingCount_);
		rawTransforms_.resize(instancingCount_);
		for(int i = 0; i < instancingCount_; i++)
		{
			transforms_[i].position = {i*50.0f, 0.0f, 0.0f};
			transforms_[i].scaleXYZ = {40.0f, 40.0f, 40.0f};
			rawTransforms_[i] = transforms_[i].get();
		}
		// cube
		geo_ = ns::Geometry::CreateCubeWithNormal();
		auto& instancingVertex = geo_->getGeoInfo().instancingVertex;
		instancingVertex.resize(rawTransforms_.size()*4);
		std::memcpy(instancingVertex.data(), rawTransforms_.data(), rawTransforms_.size()*sizeof(ns::Mat4));
		geo_->setInstancingLayout(4,4);
		geo_->updateInstancingBuffer();
	}

	bool update(double deltaTime)
	{
		auto lightColor = ns::Vec3{1.0f, 1.0f, 1.0f};
		auto lightPos = ns::Vec3{1000.0f, 1000.0f, 1000.0f};
		instancingShader_.use();
		GLGEOMETRY_CAST(geo_)->getBuffer()->bind();
		{
			instancingShader_.setVec3("lightColor", lightColor);
			instancingShader_.setVec3("objectColor", ns::Vec3{1.0f, 0.5f, 0.31f});
			instancingShader_.setMat4("view", camera_->getView());
			instancingShader_.setMat4("proj", camera_->getProj());
			instancingShader_.setVec3("lightPos", lightPos);
			instancingShader_.setVec3("viewerPos", camera_->transform.position);

			glDrawArraysInstanced(GL_TRIANGLES, 0, geo_->getGeoInfo().vertex.size(), instancingCount_);  
            // glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(geo_->getIndexSize()), GL_UNSIGNED_INT, 0, instancingCount);
            glBindVertexArray(0);
		}
		GLGEOMETRY_CAST(geo_)->getBuffer()->unbind();
		return true;
	}

private:
	ns::GlShader instancingShader_;
	ns::GlShader lightShader_;

	ns::Scene scene_{};
	ns::Entity cameraEntity_;
	ns::Camera* camera_;

	std::unique_ptr<ns::Geometry> geo_;
	std::vector<ns::Mat4> rawTransforms_;
	std::vector<ns::Transform> transforms_;

	size_t instancingCount_ = 10;
};

#endif