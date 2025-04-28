#ifndef _NS_GRAPHICS_IMGUILAYER_H_
#define _NS_GRAPHICS_IMGUILAYER_H_

#include "../common/env.h"

namespace ns::editor
{
class SDLWindow;
class ImguiLayer
{
public:
	ImguiLayer(void* window, SystemContext SystemContext);
    ~ImguiLayer();

protected:
    friend class SDLWindow;
    void predraw();
    void draw();
    void postdraw();



private:
	void init();
    void initSDL2OpenGL(void* window);

private:
    SystemContext context_;
    SDLWindow* r_window_;
};
}	 // namespace ns::editor

#endif