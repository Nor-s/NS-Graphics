#ifndef _NS_GRAPHICS_CORE_GPU_GL_GL_RENDERER_H_
#define _NS_GRAPHICS_CORE_GPU_GL_GL_RENDERER_H_

#include "glCommon.h"
#include "glBuffer.h"

namespace ns
{

class GlShader;
class Scene;
class GlRenderTarget;

enum ShaderType : size_t
{
	BASIC_SHADER = 0,
	SIZE
};

class GlRenderer
{
    using GlUniformBuffer = GlBuffer<GpuBufferTarget::UNIFORM_BUFFER, GpuBufferUsage::DYNAMIC>;
	static std::vector<std::unique_ptr<GlShader>> g_shaders;

public:
	GlRenderer();

	void render(Scene* scene);
	void onResize(const Resolution& res);	
	uint32_t getRenderTargetId();
	uint64_t getColorTexture();
	Resolution getResolution() const;

private:
	void bind();
	void unbind();
	void initShader();

private:
	std::unique_ptr<GlRenderTarget> sceneRenderTarget_;
	GlUniformBuffer cameraUniformBuffer_;
};

}	 // namespace ns

#endif
