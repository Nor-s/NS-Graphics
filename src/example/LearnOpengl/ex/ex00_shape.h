#ifndef _LEARN_GL_EX_SHAPE_H_
#define _LEARN_GL_EX_SHAPE_H_

#include "example.h"
#include <core/gpu/gl/glGeometry.h>
#include <core/gpu/gl/glShader.h>
#include <core/gpu/gl/glBuffer.h>
#include <common/common.h>

class Ex00_Shape : public Example
{
public:
	const std::string& toString() override
	{
		static const std::string ret = "ex00 shape";
		return ret;
	}
	void content() override
	{
		// shader
		vert_ = R"(
        #version 330 core
        layout (location=0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        } 
        )";
		frag_ = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        } 
        )";
		shader_.init(vert_, frag_);

		// vertex info
		geoInfo_.vertex = {
			0.5f,  0.5f,  0.0f,	   // top right
			0.5f,  -0.5f, 0.0f,	   // bottom right
			-0.5f, 0.5f,  0.0f,	   // top left
		};
		geoInfo_.index = {0, 1, 2, 0};
		// x,y,z
		uint32_t stride = 3 * sizeof(float);
		geometry_.init(geoInfo_, {ns::GlVertexLayout{0, 3, stride, 0}});
	}
	bool update(double deltaTime)
	{
		shader_.use();
		geometry_.getBuffer()->bind();
		glDrawElements(GL_TRIANGLES, geometry_.getIndexSize(), GL_UNSIGNED_INT, 0);
		geometry_.getBuffer()->unbind();
		return true;
	}

private:
	std::string vert_;
	std::string frag_;
	ns::GlShader shader_;
	ns::GlGeometry geometry_;
	ns::GeometryInfo geoInfo_;

	unsigned int VBO, VAO;
};

#endif