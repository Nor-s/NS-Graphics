#include "glRenderer.h"
#include "glShader.h"

namespace ns
{
std::vector<std::unique_ptr<GlShader>> GlRenderer::g_shaders {};

std::unique_ptr<GlShader> basicShader()
{
    std::string vert = R"(
        #version 330 core
        layout (location=0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        } 
        )";

	std::string frag = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 color;

        void main()
        {
            FragColor = color;
        } 
        )";
    std::unique_ptr<GlShader> shader = std::make_unique<GlShader>();
	shader->init(vert, frag);
    return shader;
}


void GlRenderer::initShader()
{
    g_shaders.reserve(ShaderType::SIZE);

    g_shaders.push_back(basicShader());
}


}