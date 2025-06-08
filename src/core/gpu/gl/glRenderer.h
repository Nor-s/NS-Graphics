#ifndef _NS_GRAPHICS_CORE_GPU_GL_GL_RENDERER_H_
#define _NS_GRAPHICS_CORE_GPU_GL_GL_RENDERER_H_

#include "glCommon.h"

namespace ns
{

class GlShader;


enum ShaderType: size_t
{
    BASIC_SHADER = 0,
    SIZE
};

class GlRenderer
{
    static std::vector<std::unique_ptr<GlShader>> g_shaders;

public:
    GlRenderer();

private:
	void initShader();

};

}	 // namespace ns

#endif
