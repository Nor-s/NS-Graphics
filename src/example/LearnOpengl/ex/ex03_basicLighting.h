#ifndef _LEARN_GL_EX_03_BASIC_LIGHTING_H_
#define _LEARN_GL_EX_03_BASIC_LIGHTING_H_

#include "example.h"
/**
 * 
https://learnopengl.com/Lighting/Basic-Lighting

Ambient lighting: 
- even when it is dark there is usually still some light somewhere in the world (the moon, a distant light) 
- so objects are almost never completely dark. 
- To simulate this we use **an ambient lighting constant** that always gives the object some color.

Diffuse lighting: 
- simulates **the directional impact** a light object has on an object. 
- This is the most visually significant component of the lighting model. 
- The more a part of an object faces the light source, the brighter it becomes.

Specular lighting: 
- simulates the bright spot of a light that appears on shiny objects. 
- Specular highlights are more inclined to **the color of the light** than the color of the object.  

 */
class Ex03_BasicLighting : public Example
{
public:
	const std::string& toString() override
	{
		static const std::string ret = "ex03 basicLighting";
		return ret;
	}
	~Ex03_BasicLighting()
	{
		destroy();
	}
	void destroy()
	{
		using namespace ns::editor;
		App::SetCurrentInputController(nullptr);
		inputController_ = std::make_unique<ns::InputController>();
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

		basicLightVert_ = R"(
        #version 330 core

        layout (location=0) in vec3 aPos;
        layout (location=1) in vec3 aNormal;

		uniform mat4 transform;
		uniform mat4 view;
		uniform mat4 proj;

		out vec3 normal;
		out vec3 fragPos;
  
		void main()
        {
			gl_Position = proj*view*transform * vec4(aPos, 1.0f);
			normal = aNormal;

			fragPos = vec3(transform*vec4(aPos, 1.0)); // frag world position
        } 
        )";

		basicLightFrag_ = R"(
        #version 330 core

		in vec3 normal;
		in vec3 fragPos;

        out vec4 FragColor;

		uniform vec3 objectColor;
		uniform vec3 lightColor;
		uniform vec3 lightPos;
		uniform vec3 viewerPos;

        void main()
        {
			float ambientStrength = 0.1f;
			vec3 ambient = ambientStrength * lightColor;

            //FragColor = vec4(ambient*objectColor, 1.0f);

			vec3 toFace = normalize(normal);
			vec3 toLight = normalize(lightPos - fragPos);
			float diff = max(dot(toFace, toLight), 0.0f);
			vec3 diffuse = diff * lightColor;

			// vec3 result = (ambient + diffuse) * objectColor;
			// FragColor = vec4(result, 1.0f);

			// if calculate lighting in view space... view pos = (0, 0, 0)
			float specularStrencth = 0.5f;
			vec3 viewDir = normalize(viewerPos - fragPos);
			vec3 reflectDir = reflect(-toLight, toFace);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
			vec3 specular = specularStrencth * spec * lightColor;

			vec3 result = (ambient + diffuse + specular) * objectColor;
			FragColor = vec4(result, 1.0f);
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
		basicLightShader_.init(basicLightVert_, basicLightFrag_);
		lightObjectShader_.init(vert_, lightObjectFrag_);

		using namespace ns::editor;

		auto res = App::GetAppContext().res;

		cubeCount_ = 10;

		// set cube object
		object_.cube = ns::GlGeometry::genCubeWithNormal();
		object_.transform.scaleXYZ = ns::Vec3{0.4f, 0.4f, 0.4f};

		lightObject_.cube = ns::GlGeometry::genCube();
		float lightSize = cubeCount_*0.1f;
		lightObject_.transform.scaleXYZ = ns::Vec3{lightSize, lightSize, lightSize};
		lightObject_.transform.position = ns::Vec3{cubeCount_*1.5f, 0.0f, 0.0f};

		// set camera
		camera_.setRes(res);
		camera_.setOrthoFactor({(float) res.width/80, (float) res.height/80});
		camera_.setPosition({100, 100, 100});
		camera_.setTarget({0.0, 0.0, 0.0});
		camera_.setFov(ns::math::ToRadian(45.0f));
		camera_.setPerspective();

		// input controller
		inputController_ = std::make_unique<ns::InputController>();
		inputController_->bindAction(
			ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN),
			ns::InputTrigger::Started,this,
			&Ex03_BasicLighting::moveStartCamera
		);
		inputController_->bindAction(
			ns::InputAction(ns::InputType::MOUSE_LEFT_DOWN),
			ns::InputTrigger::Triggered,this,
			&Ex03_BasicLighting::moveCamera
		);
		inputController_->bindAction(
			ns::InputAction(ns::InputType::MOUSE_WHEEL),
			ns::InputTrigger::Triggered, this,
			&Ex03_BasicLighting::moveWheel
		);
		App::SetCurrentInputController(inputController_.get());
	}
	bool update(double deltaTime)
	{
		basicLightShader_.use();
		auto lightColor = ns::Vec3{1.0f, 1.0f, 1.0f};

		{
			object_.cube->getBuffer()->bind();
			basicLightShader_.setVec3("lightColor", lightColor);
			basicLightShader_.setVec3("objectColor", ns::Vec3{1.0f, 0.5f, 0.31f});
			basicLightShader_.setMat4("view", camera_.getView());
			basicLightShader_.setMat4("proj", camera_.getProj());
			basicLightShader_.setVec3("lightPos", lightObject_.transform.position);
			basicLightShader_.setVec3("viewerPos", camera_.getTransform().position);

			auto before = object_.transform.position;

			for(int i = 0 ; i < cubeCount_; i++)
			{
				for(int j = 0; j < cubeCount_; j++)
				{
					for(int k = 0; k < cubeCount_; k++)
					{
						object_.transform.position = before + ns::Vec3{i*1.0f, j*1.0f, k*1.0f};
						basicLightShader_.setMat4("transform", object_.transform.get());
						glDrawArrays(GL_TRIANGLES, 0, 36);
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
			lightObjectShader_.setMat4("view", camera_.getView());
			lightObjectShader_.setMat4("proj", camera_.getProj());

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

		if(ImGui::IsWindowFocused())
		{
			App::SetCurrentInputController(nullptr);
		}
		else 
		{
			App::SetCurrentInputController(inputController_.get());
		}
	}

public:
	void moveStartCamera(const ns::InputValue& value)
	{
		beforeMousePos_ = value.get<ns::Vec2>();
		NS_LOG("start camera, x {}, y {}", beforeMousePos_.x, beforeMousePos_.y);
	}
	void moveCamera(const ns::InputValue& value)
	{
		// camera Pos -  camera Target 
		auto currentMousePos = value.get<ns::Vec2>();
		auto delta =  currentMousePos - beforeMousePos_;
		beforeMousePos_ = currentMousePos;
		delta.x*=-1.0f;

		auto at = camera_.getTarget();
		auto up = camera_.getUp();
		auto eye = camera_.getTransform().position;
		auto relCameraPos = eye - at;
		auto forwardDir = ns::normalize(relCameraPos);
		auto rightDir = ns::normalize(ns::cross(up, forwardDir));
		auto upDir = ns::normalize(ns::cross(forwardDir, rightDir));
		auto len = ns::length2(relCameraPos);

		auto nextRelPos = relCameraPos + upDir*delta.y + rightDir * delta.x;

		auto targetDir = ns::normalize(nextRelPos);
		auto theta = acos(targetDir*forwardDir);

		if(theta < 0.001f)
		{
			return;
		}
		auto axis = ns::cross(forwardDir, targetDir);
		if(ns::length2(axis) < 0.001f)
		{
			return;
		}
		axis = ns::normalize(axis);

		auto rot = ns::rotate(ns::Mat4(), axis, theta);
		auto nextRelP = static_cast<ns::Vec3>(rot*ns::Vec4(relCameraPos, 1.0f));
		auto nextDot = ns::normalize(nextRelP) * up;
		if(abs(nextDot) > 0.97f)
		{
			return;
		}

		camera_.getMutableTransform().position = nextRelP + at;

		NS_LOG("move camera, x {}, y {}", delta.x, delta.y);
	}
	void moveWheel(const ns::InputValue& value)
	{
		float speed = 1.0f;
		float x = value.get<float>();

		auto at = camera_.getTarget();
		auto up = camera_.getUp();
		auto eye = camera_.getTransform().position;
		auto relCameraPos = eye - at;
		auto forwardDir = ns::normalize(relCameraPos);

		auto next = forwardDir*speed*x + relCameraPos;

		if(ns::length2(next) > 30.0f)
		{
			camera_.getMutableTransform().position = next + at;
		}

		NS_LOG("move wheel, x {}", x);
	}


private:
	int cubeCount_ = 1;

	std::string vert_{};
	std::string basicLightVert_{};
	std::string basicLightFrag_{};
	std::string lightObjectFrag_{};

	ns::GlShader basicLightShader_{};
	ns::GlShader lightObjectShader_{};

	float angle_{};
	ExEntity object_;
	ExEntity lightObject_;

	ns::CameraEntity camera_;
	ns::Vec2 beforeMousePos_;
};

#endif