#include "glRenderer.h"
#include "glShader.h"
#include "core/entity/component/nsMaterial.h"

namespace ns
{
std::unordered_map<const char*, std::unique_ptr<GlShader>> GlRenderer::g_shaders {};

std::unique_ptr<GlShader> CreateGLBasicLightShader()
{
    std::string vert = R"(
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

	std::string frag = R"(
        #version 330 core

		in vec3 normal;
		in vec3 fragPos;

        out vec4 FragColor;

		uniform vec3 color;
		uniform vec3 lightColor;
		uniform vec3 lightPos;
		uniform vec3 eyeWorldPosition;

        void main()
        {
			float ambientStrength = 0.1f;
			vec3 ambient = ambientStrength * lightColor;

			vec3 toFace = normalize(normal);
			vec3 toLight = normalize(lightPos - fragPos);
			float diff = max(dot(toFace, toLight), 0.0f);
			vec3 diffuse = diff * lightColor;

			// if calculate lighting in view space... view pos = (0, 0, 0)
			float specularStrencth = 0.5f;
			vec3 viewDir = normalize(eyeWorldPosition - fragPos);
			vec3 reflectDir = reflect(-toLight, toFace);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
			vec3 specular = specularStrencth * spec * lightColor;

			vec3 result = (ambient + diffuse + specular) * color;
			FragColor = vec4(result, 1.0f);
        } 
        )";
    std::unique_ptr<GlShader> shader = std::make_unique<GlShader>();
	shader->init(vert, frag);
    return shader;
}

std::unique_ptr<GlShader> CreateGLSolidLightShader()
{
    std::string vert = R"(
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

	std::string frag = R"(
        #version 330 core
        out vec4 FragColor;
		uniform vec3 color;

        void main()
        {
            FragColor = vec4(color, 1.0);
        } 
        )";
    std::unique_ptr<GlShader> shader = std::make_unique<GlShader>();
	shader->init(vert, frag);
    return shader;
}

std::unique_ptr<GlShader> CreateBasicLightInstancingShader()
{
    std::string vert = R"(
        #version 330 core

        layout (location=0) in vec3 aPos;
        layout (location=1) in vec3 aNormal;
        layout (location = 4) in mat4 instanceMatrix;
        layout (location = 8) in vec4 inputColor;

		uniform mat4 view;
		uniform mat4 proj;

		out vec3 normal;
		out vec3 fragPos;
		out vec4 color;
  
		void main()
        {
			gl_Position = proj*view*instanceMatrix* vec4(aPos, 1.0f);
			normal = aNormal;

			fragPos = vec3(instanceMatrix*vec4(aPos, 1.0)); // frag world position
			color = inputColor;
        } 
        )";

	std::string frag = R"(
        #version 330 core

		in vec3 normal;
		in vec3 fragPos;
		in vec4 color;

        out vec4 FragColor;

		uniform vec3 lightColor;
		uniform vec3 lightPos;
		uniform vec3 eyeWorldPosition;

        void main()
        {
			if(color.r < 0.0f)
			{
				discard;
				return;
			}
			float ambientStrength = 0.8f;
			vec3 ambient = ambientStrength * lightColor;

			vec3 toFace = normalize(normal);
			vec3 toLight = normalize(lightPos - fragPos);
			float diff = max(dot(toFace, toLight), 0.0f);
			vec3 diffuse = diff * lightColor;

			// if calculate lighting in view space... view pos = (0, 0, 0)
			float specularStrencth = 0.5f;
			vec3 viewDir = normalize(eyeWorldPosition - fragPos);
			vec3 reflectDir = reflect(-toLight, toFace);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
			vec3 specular = specularStrencth * spec * lightColor;

			vec3 result = (ambient + diffuse + specular) * color.xyz;
			FragColor = vec4(result, 1.0f);
        } 
        )";	

	std::unique_ptr<GlShader> shader = std::make_unique<GlShader>();
	shader->init(vert, frag);
    return shader;
}


void GlRenderer::initShader()
{
    if(g_shaders.size() != 0) return;
    
    g_shaders[BasicLightMaterial::name] = CreateGLBasicLightShader();
    g_shaders[SolidColorMaterial::name] = CreateGLSolidLightShader();
	g_shaders[BasicLightInstancingMaterial::name] = CreateBasicLightInstancingShader();
}


}