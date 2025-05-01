#ifndef _NS_GRAPHICS_IMGUILAYER_H_
#define _NS_GRAPHICS_IMGUILAYER_H_

#include <vector>
#include <memory>
#include "../common/env.h"
#include "imguiModule.h"

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

    void drawDoc();
    void setDocMode(bool bIsDocMode = true);
    void addModule(std::unique_ptr<IImguiModule> module);

private:
	void init();
    void initSDL2OpenGL(void* window);

private:
    SystemContext context_;
    SDLWindow* r_window_;

    bool bIsDocMode_ = true;

    std::vector<std::unique_ptr<IImguiModule>> modules_;
};
}	 // namespace ns::editor

#endif