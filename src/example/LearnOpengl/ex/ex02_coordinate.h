#ifndef _LEARN_GL_EX_02_COORDINATE_H_
#define _LEARN_GL_EX_02_COORDINATE_H_

#include <cmath>
#include "example.h"

#include <core/gpu/gl/glGeometry.h>
#include <core/gpu/gl/glShader.h>
#include <core/gpu/gl/glBuffer.h>
#include <editor/app.h>

#include <common/common.h>

#include <editor/imgui/imguiComponents.h>

struct ExEntity
{
	std::unique_ptr<ns::GlGeometry> cube = nullptr;
	ns::Transform transform;
};

class Ex02_Coordinate : public Example
{

public:
	const std::string& toString() override
	{
		static const std::string ret = "ex02 coordinate";
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

		frag_ = R"(
        #version 330 core
        out vec4 FragColor;
		uniform vec4 color;

        void main()
        {
            FragColor = color;
        } 
        )";
		shader_.init(vert_, frag_);

		using namespace ns::editor;

		cube_.cube = ns::GlGeometry::genRectangle();
		camera_.setRes(App::GetAppContext().res);
		camera_.setPosition({0, 0, -1});
		camera_.setTarget({0.0, 0.0, 0.0});
	}

	bool update(double deltaTime)
	{
		shader_.use();

		{
			cube_.cube->getBuffer()->bind();
			shader_.setVec4("color", ns::Vec4{0.0f, 4.0f, 1.0f, 1.0f});
			shader_.setMat4("transform", cube_.transform.get());
			shader_.setMat4("view", camera_.getView());
			shader_.setMat4("proj", camera_.getProj());
			glDrawElements(GL_TRIANGLES, cube_.cube->getIndexSize(), GL_UNSIGNED_INT, 0);
			cube_.cube->getBuffer()->unbind();
		}

		return true;
	}

	void drawUIWidgets()
	{
		ImGuiEx::DragPropertyXYZ("scale", cube_.transform.scaleXYZ.value, 0.1f, 0.1f, 3.0f);
		ImGuiEx::DragPropertyXYZ("translate", cube_.transform.position.value, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("angle", &angle_, 1.0f, -360.0f, 360.0f);
		cube_.transform.radianXYZ.z = angle_*3.141592f/180.0f ;

		// camera
		ImGuiEx::DragPropertyXYZ("camera pos", camera_.getMutableTransform().position.value, 0.1f, -4.0f, 4.0f);
		ImGuiEx::DragPropertyXYZ("target pos", camera_.getMutableTarget().value, 0.1f, -4.0f, 4.0f);

		using namespace ns::editor;
		auto windowRes = App::GetAppContext().res;
		auto ortho = camera_.getOrthoFactor();

		ImGui::Text("window width: %d, window height: %d", windowRes.width, windowRes.height);
		ImGui::DragFloat("ortho_factor_x", &ortho.x, 1.0f, 1.0f, 4000.0f);
		ImGui::DragFloat("ortho_factor_y", &ortho.y, 1.0f, 1.0f, 4000.f);

		camera_.setOrthoFactor(ortho);
	}

private:
	std::string vert_{};
	std::string frag_{};
	ns::GlShader shader_{};
	float angle_{};
	ExEntity cube_;
	ns::CameraEntity camera_;
};

#endif