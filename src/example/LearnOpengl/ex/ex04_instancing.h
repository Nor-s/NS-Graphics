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

		instancingCount_ = instancingLength_*instancingLength_*instancingLength_;
		transforms_.resize(instancingCount_);
		rawTransforms_.resize(instancingCount_);
		std::vector<ns::Vec4> colors;
		for(int i = 0; i < instancingLength_; i++)
		{
			for(int j = 0; j < instancingLength_; j++)
			{
				for(int k = 0; k < instancingLength_; k++)
				{
					int idx = i*instancingLength_*instancingLength_ + j*instancingLength_ + k;
					transforms_[idx].position = {i*50.0f, j*50.0f, k*50.0f};
					transforms_[idx].scaleXYZ = {40.0f, 40.0f, 40.0f};
					rawTransforms_[idx] = transforms_[idx].get();
					colors.push_back({float(i)/instancingLength_, float(i)/instancingLength_, float(i)/instancingLength_, 1.0f});
				}
			}
		}
		// cube
		geo_ = ns::Geometry::CreateCubeWithNormal();
		geo_->pushInstancingLayout(4,4);
		geo_->updateInstancingBuffer(0, rawTransforms_.size()*sizeof(ns::Mat4), rawTransforms_.data());
		geo_->pushInstancingLayout(8,1);
		geo_->updateInstancingBuffer(1, colors.size()*sizeof(ns::Vec4), colors.data());

		initCameraInputController();
		mainCameraTransform_->position = {1500, 1500, 1500};
	}

	bool update(double deltaTime)
	{
		auto lightColor = ns::Vec3{1.0f, 1.0f, 1.0f};
		auto lightPos = ns::Vec3{1000.0f, 1000.0f, 1000.0f};
		instancingShader_.use();
		GLGEOMETRY_CAST(geo_)->getBuffer()->bind();
		{
			instancingShader_.setVec3("lightColor", lightColor);
			instancingShader_.setMat4("view", mainCamera_->getView());
			instancingShader_.setMat4("proj", mainCamera_->getProj());
			instancingShader_.setVec3("lightPos", lightPos);
			instancingShader_.setVec3("viewerPos", mainCamera_->transform.position);

			glDrawArraysInstanced(GL_TRIANGLES, 0, geo_->getGeoInfo().vertex.size(), instancingCount_);  
            // glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(geo_->getIndexSize()), GL_UNSIGNED_INT, 0, instancingCount);
		}
		GLGEOMETRY_CAST(geo_)->getBuffer()->unbind();
		return true;
	}

	virtual void drawUIWidgets() override
	{
		drawCameraUI();
	}

private:
	ns::GlShader instancingShader_;
	ns::GlShader lightShader_;

	std::unique_ptr<ns::Geometry> geo_;
	std::vector<ns::Mat4> rawTransforms_;
	std::vector<ns::Transform> transforms_;

	size_t instancingLength_ = 10;
	size_t instancingCount_ = 1000;
};

#endif