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

		cubeCount_ = 10;

		// set cube object
		object_.cube = ns::Geometry::CreateCubeWithNormal();
		object_.transform.scaleXYZ = ns::Vec3{0.4f, 0.4f, 0.4f};

		lightObject_.cube = ns::Geometry::CreateCube();
		float lightSize = cubeCount_*0.1f;
		lightObject_.transform.scaleXYZ = ns::Vec3{lightSize, lightSize, lightSize};
		lightObject_.transform.position = ns::Vec3{cubeCount_*1.5f, 0.0f, 0.0f};

		initCameraInputController();
	}
	bool update(double deltaTime)
	{
		basicLightShader_.use();
		auto lightColor = ns::Vec3{1.0f, 1.0f, 1.0f};
		{
			GLGEOMETRY_CAST(object_.cube)->getBuffer()->bind();
			basicLightShader_.setVec3("lightColor", lightColor);
			basicLightShader_.setVec3("objectColor", ns::Vec3{1.0f, 0.5f, 0.31f});
			basicLightShader_.setMat4("view", mainCamera_->getView());
			basicLightShader_.setMat4("proj", mainCamera_->getProj());
			basicLightShader_.setVec3("lightPos", lightObject_.transform.position);
			basicLightShader_.setVec3("viewerPos", mainCameraTransform_->position);

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
			GLGEOMETRY_CAST(object_.cube)->getBuffer()->unbind();
		}

		lightObjectShader_.use();
		{
			GLGEOMETRY_CAST(lightObject_.cube)->getBuffer()->bind();
			lightObjectShader_.setVec3("lightColor", lightColor);
			lightObjectShader_.setMat4("transform", lightObject_.transform.get());
			lightObjectShader_.setMat4("view", mainCamera_->getView());
			lightObjectShader_.setMat4("proj", mainCamera_->getProj());

			glDrawElements(GL_TRIANGLES, lightObject_.cube->getIndexSize(), GL_UNSIGNED_INT, 0);

			GLGEOMETRY_CAST(lightObject_.cube)->getBuffer()->unbind();
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
		
		drawCameraUI();
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
};

#endif