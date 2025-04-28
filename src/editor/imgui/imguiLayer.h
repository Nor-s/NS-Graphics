#ifndef _NS_GRAPHICS_IMGUILAYER_H_
#define _NS_GRAPHICS_IMGUILAYER_H_

#include "../common/env.h"

namespace ns::editor
{
class ImguiLayer
{
public:
	ImguiLayer(void* window, SystemContext SystemContext);
    ~ImguiLayer();

private:
	void init();
    void initSDL2OpenGL(void* window);

private:
    SystemContext context_;
};
}	 // namespace ns::editor

#endif