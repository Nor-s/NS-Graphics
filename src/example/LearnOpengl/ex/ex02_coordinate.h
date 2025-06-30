#ifndef _LEARN_GL_EX_02_COORDINATE_H_
#define _LEARN_GL_EX_02_COORDINATE_H_

#include "example.h"

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

		auto res = App::GetAppContext().res;
		cube_.cube = ns::Geometry::CreateCube();
		camera_.setRes(res);
		camera_.setOrthoFactor({(float) res.width, (float) res.height});
		camera_.transform.position = {0, 0, 5};
		camera_.setTarget({0.0, 0.0, 0.0});
	}

	bool update(double deltaTime)
	{
		shader_.use();
		auto* geometry = static_cast<ns::GlGeometry*>(cube_.cube.get());
		{
			geometry->getBuffer()->bind();
			shader_.setVec4("color", ns::Vec4{0.0f, 4.0f, 1.0f, 1.0f});
			shader_.setMat4("transform", cube_.transform.get());
			shader_.setMat4("view", camera_.getView());
			shader_.setMat4("proj", camera_.getProj());

			glDrawElements(GL_TRIANGLES, cube_.cube->getIndexSize(), GL_UNSIGNED_INT, 0);
			geometry->getBuffer()->unbind();
		}

		return true;
	}

	void drawUIWidgets()
	{
		ImGuiEx::DragPropertyXYZ("scale", cube_.transform.scaleXYZ.value, 0.1f, 0.1f, 3.0f);
		ImGuiEx::DragPropertyXYZ("translate", cube_.transform.position.value, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("angle", &angle_, 1.0f, -360.0f, 360.0f);
		cube_.transform.radianXYZ.z = angle_ * 3.141592f / 180.0f;

		// camera
		ImGuiEx::DragPropertyXYZ("camera pos", camera_.transform.position.value, 0.1f, -10.0f, 10.0f);
		ImGuiEx::DragPropertyXYZ("target pos", camera_.getMutableTarget().value, 0.1f, -10.0f, 10.0f);

		using namespace ns::editor;
		auto windowRes = App::GetAppContext().res;
		auto ortho = camera_.getOrthoFactor();

		ImGui::Text("window width: %d, window height: %d", windowRes.width, windowRes.height);
		ImGui::DragFloat("ortho_factor_x", &ortho.x, 1.0f, 1.0f, 4000.0f);
		ImGui::DragFloat("ortho_factor_y", &ortho.y, 1.0f, 1.0f, 4000.f);

		camera_.setOrthoFactor(ortho);

		ImGui::Checkbox("Is Ortho", &bIsOrtho_);
		camera_.setMode(bIsOrtho_ ? ns::CameraMode::OrthoRH : ns::CameraMode::PerspectRH);

		ImGui::DragFloat("fov", &fov_, 1.0f, 0.0f, 360.f);
		camera_.setFov(fov_ *(M_PI/180.0f));
	}

private:
	std::string vert_{};
	std::string frag_{};
	ns::GlShader shader_{};
	float angle_{};
	ExEntity cube_;
	ns::Camera camera_;
	bool bIsOrtho_ = false;
	float fov_=45.0f;
};

#endif