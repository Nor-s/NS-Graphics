#ifndef _LEARN_GL_EX_03_BASIC_LIGHTING_H_
#define _LEARN_GL_EX_03_BASIC_LIGHTING_H_

#include "example.h"

class Ex03_BasicLighting : public Example
{
public:
	const std::string& toString() override
	{
		static const std::string ret = "ex03 basicLighting";
		return ret;
	}
	void content() override
	{
		// shader
		vert_ = R"(
        #version 330 core
        layout (location=0) in vec3 aPos;
		uniform mat4 transform;
		uniform mat4 view;
		uniform mat4 proj;
  
		void main()
        {
			gl_Position = proj*view*transform * vec4(aPos, 1.0f);
        } 
        )";

		lightFrag_ = R"(
        #version 330 core
        out vec4 FragColor;
		uniform vec3 objectColor;
		uniform vec3 lightColor;

        void main()
        {
            FragColor = vec4(lightColor*objectColor, 1.0);
        } 
        )";

		lightObjectFrag_ = R"(
        #version 330 core
        out vec4 FragColor;
		uniform vec3 lightColor;

        void main()
        {
            FragColor = vec4(lightColor, 1.0);
        } 
        )";
		lightShader_.init(vert_, lightFrag_);
		lightObjectShader_.init(vert_, lightObjectFrag_);

		using namespace ns::editor;

		auto res = App::GetAppContext().res;

		cubeCount_ = 30;

		// set cube object
		object_.cube = ns::GlGeometry::genCube();
		object_.transform.scaleXYZ = ns::Vec3{0.4f, 0.4f, 0.4f};

		lightObject_.cube = ns::GlGeometry::genCube();
		float lightSize = cubeCount_*0.1f;
		lightObject_.transform.scaleXYZ = ns::Vec3{lightSize, lightSize, lightSize};
		lightObject_.transform.position = ns::Vec3{cubeCount_*1.5f, 0.0f, 0.0f};

		// set camera
		camera_.setRes(res);
		camera_.setOrthoFactor({(float) res.width/80, (float) res.height/80});
		camera_.setPosition({300, 300, 300});
		camera_.setTarget({0.0, 0.0, 0.0});
	}

	bool update(double deltaTime)
	{
		lightShader_.use();
		auto lightColor = ns::Vec3{1.0f, 1.0f, 1.0f};

		{
			object_.cube->getBuffer()->bind();
			lightShader_.setVec3("lightColor", lightColor);
			lightShader_.setVec3("objectColor", ns::Vec3{1.0f, 0.5f, 0.31f});
			lightShader_.setMat4("view", camera_.getView());
			lightShader_.setMat4("proj", camera_.getProj());

			auto before = object_.transform.position;

			for(int i = 0 ; i < cubeCount_; i++)
			{
				for(int j = 0; j < cubeCount_; j++)
				{
					for(int k = 0; k < cubeCount_; k++)
					{
						object_.transform.position = before + ns::Vec3{i*1.0f, j*1.0f, k*1.0f};
						lightShader_.setMat4("transform", object_.transform.get());
						glDrawElements(GL_TRIANGLES, object_.cube->getIndexSize(), GL_UNSIGNED_INT, 0);
					}	
				}
			}
			object_.transform.position = before;
			object_.cube->getBuffer()->unbind();
		}

		lightObjectShader_.use();
		{
			lightObject_.cube->getBuffer()->bind();
			lightObjectShader_.setVec3("lightColor", lightColor);
			lightObjectShader_.setMat4("transform", lightObject_.transform.get());
			lightShader_.setMat4("view", camera_.getView());
			lightShader_.setMat4("proj", camera_.getProj());

			glDrawElements(GL_TRIANGLES, lightObject_.cube->getIndexSize(), GL_UNSIGNED_INT, 0);

			lightObject_.cube->getBuffer()->unbind();
		}

		return true;
	}

	void drawUIWidgets()
	{
		using namespace ns::editor;

		ImGui::Text("object");
		ImGuiEx::DragPropertyXYZ("scale", object_.transform.scaleXYZ.value, 0.1f, 0.1f, 3.0f);
		ImGuiEx::DragPropertyXYZ("translate", object_.transform.position.value, 0.01f, -100.0f, 100.0f);
		ImGui::DragFloat("angle", &angle_, 1.0f, -360.0f, 360.0f);
		object_.transform.radianXYZ.z = angle_ * 3.141592f / 180.0f;

		// light
		ImGuiEx::DragPropertyXYZ("light object", lightObject_.transform.position.value, 0.01f, -100.0f, 100.0f);



		// camera
		ImGuiEx::DragPropertyXYZ("camera pos", camera_.getMutableTransform().position.value, 1.0f, -400.0f, 400.0f);
		ImGuiEx::DragPropertyXYZ("target pos", camera_.getMutableTarget().value, 0.1f, -10.0f, 10.0f);

		// ortho camera
		auto windowRes = App::GetAppContext().res;
		auto ortho = camera_.getOrthoFactor();

		ImGui::Text("window width: %d, window height: %d", windowRes.width, windowRes.height);

		ImGui::DragFloat("ortho_factor_x", &ortho.x, 1.0f, 1.0f, 4000.0f);
		ImGui::DragFloat("ortho_factor_y", &ortho.y, 1.0f, 1.0f, 4000.f);

		float f = windowRes.width/ortho.x;
		ImGui::DragFloat("ortho factor", &f, 1.0f, 1.0f, windowRes.width);

		camera_.setOrthoFactor(ortho);
		camera_.setOrthoFactor({(float) windowRes.width/f, (float) windowRes.height/f});
	}

private:
	int cubeCount_ = 1;

	std::string vert_{};
	std::string lightFrag_{};
	std::string lightObjectFrag_{};

	ns::GlShader lightShader_{};
	ns::GlShader lightObjectShader_{};

	float angle_{};
	ExEntity object_;
	ExEntity lightObject_;

	ns::CameraEntity camera_;
};

#endif