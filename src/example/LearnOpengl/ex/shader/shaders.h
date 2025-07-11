#ifndef _LEARNGL_SHADERS_H_
#define _LEARNGL_SHADERS_H_

#include <string>

class Shaders
{
public:

inline static constexpr const char* basicVert = R"(
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

inline static constexpr const char* basicLighInstancingtVert = R"(
        #version 330 core

        layout (location=0) in vec3 aPos;
        layout (location=1) in vec3 aNormal;
        layout (location = 4) in mat4 instanceMatrix;

		uniform mat4 view;
		uniform mat4 proj;

		out vec3 normal;
		out vec3 fragPos;
  
		void main()
        {
			gl_Position = proj*view*instanceMatrix* vec4(aPos, 1.0f);
			normal = aNormal;

			fragPos = vec3(instanceMatrix*vec4(aPos, 1.0)); // frag world position
        } 
        )";
	inline static constexpr const char* basicLightFrag = R"(
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

			vec3 toFace = normalize(normal);
			vec3 toLight = normalize(lightPos - fragPos);
			float diff = max(dot(toFace, toLight), 0.0f);
			vec3 diffuse = diff * lightColor;

			float specularStrencth = 0.5f;
			vec3 viewDir = normalize(viewerPos - fragPos);
			vec3 reflectDir = reflect(-toLight, toFace);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
			vec3 specular = specularStrencth * spec * lightColor;

			vec3 result = (ambient + diffuse + specular) * objectColor;
			FragColor = vec4(result, 1.0f);
        } 
        )";

	inline static constexpr const char* solidColorFrag = R"(
        #version 330 core
        out vec4 FragColor;
		uniform vec3 lightColor;

        void main()
        {
            FragColor = vec4(lightColor, 1.0);
        } 
        )";
};

#endif