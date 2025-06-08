#ifndef _NS_GRAPHICS_CORE_GPU_GL_GL_RENDER_TASK_H_
#define _NS_GRAPHICS_CORE_GPU_GL_GL_RENDER_TASK_H_

namespace ns
{
class GlShader;

class GlRenderTask
{
public:
    GlRenderTask(GlShader* shader): shader_(shader){}

    void run();

private:
    GlShader* shader_;
};

}	 // namespace ns

#endif