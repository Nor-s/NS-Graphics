#ifndef _NS_GRAPHICS_EDITOR_WINDOW_H_
#define _NS_GRAPHICS_EDITOR_WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <string>
#include <string_view>
#include <memory>

#include <core/platform/platformEvent.h>

#include "../common/env.h"

namespace ns::editor
{
class ImguiLayer;

class SDLWindow
{
public:
    SDLWindow(AppContext appContext, SystemContext sysContext);
    ~SDLWindow();

    SDL_Window* getHandle(){return handle_;}
    SDL_GLContext& getGLContext(){return context_;}
    void processEvent(SystemIO& io);

private:
    void initGL();

private:
    AppContext appContext_;
    SystemContext sysContext_;
    SDL_Window* handle_ = nullptr;
    SDL_GLContext context_;

    std::unique_ptr<ImguiLayer> imguiLayer_;
};

}	 // namespace ns::editor
#endif