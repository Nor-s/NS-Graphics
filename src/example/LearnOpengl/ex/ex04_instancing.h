#ifndef _LEARN_GL_EX_04_INSTANCING_H_
#define _LEARN_GL_EX_04_INSTANCING_H_

#include <core/gpu/gl/glGeometry.h>
#include "example.h"
#include <core/entity/component/components.h>
#include <core/scene/nsScene.h>
#include "shader/shaders.h"

#define GLGEOMETRY_CAST(geo) static_cast<ns::GlGeometry*>(geo.get())

/**
https://learnopengl.com/Advanced-OpenGL/Instancing


 */
class Ex04_Instancing : public Example
{
public:
	const std::string& toString() override
	{
		return "ex04 Instancing";
	}
	~Ex04_Instancing()
	{
		destroy();
	}
	void destroy()
	{
	}
	void content() override
	{
		instancingShader_.init(Shaders::basicLighInstancingtVert, Shaders::basicLightFrag);
		lightShader_.init(Shaders::basicVert, Shaders::solidColorFrag);

	}

	bool update(double deltaTime)
	{
		return true;
	}

private:
	ns::GlShader instancingShader_;
	ns::GlShader lightShader_;
};

#endif