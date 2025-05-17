#ifndef _LEARN_GL_EX_01_TRANSFORM_H_
#define _LEARN_GL_EX_01_TRANSFORM_H_

#include <cmath>
#include "example.h"
#include <core/gpu/gl/glGeometry.h>
#include <core/gpu/gl/glShader.h>
#include <core/gpu/gl/glBuffer.h>
#include <common/common.h>

#include <editor/imgui/imguiComponents.h>

class Ex01_Transform : public Example
{
public:
	const std::string& toString() override
	{
		static const std::string ret = "ex01 transform";
		return ret;
	}
	void content() override
	{
		// shader
		vert_ = R"(
        #version 330 core
        layout (location=0) in vec3 aPos;
		uniform mat4 transform;
  
		void main()
        {
			gl_Position = transform * vec4(aPos, 1.0f);
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

		cube_ = ns::GlGeometry::genRectangle();
	}
	bool update(double deltaTime)
	{
		shader_.use();

		{
			cube_->getBuffer()->bind();
			shader_.setVec4("color", ns::Vec4{0.0f, 4.0f, 1.0f, 1.0f});
			{
				// T * S * R
				auto transform = ns::translate({}, translate_);
				transform = ns::scale(transform, scale_);
				transform = ns::rotateZ(transform, angle_ * 3.141592 / 180.0);
				shader_.setMat4("transform", transform);
			}
			glDrawElements(GL_TRIANGLES, cube_->getIndexSize(), GL_UNSIGNED_INT, 0);
			cube_->getBuffer()->unbind();
		}

		return true;
	}
	void drawUIWidgets()
	{
		ImGuiEx::DragPropertyXYZ("scale", scale_.value, 0.1f, 0.1f, 3.0f);
		ImGuiEx::DragPropertyXYZ("translate", translate_.value, 0.01f, -1.0f, 1.0f);
		ImGui::DragFloat("angle", &angle_, 1.0f, -360.0f, 360.0f);
	}

private:
	std::string vert_{};
	std::string frag_{};
	ns::GlShader shader_{};
	std::unique_ptr<ns::GlGeometry> cube_ = nullptr;
	ns::Vec3 translate_{};
	ns::Vec3 scale_{1.0f, 1.0f, 1.0f};
	float angle_{};
};

#endif