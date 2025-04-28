#include "SDLWindow.h"

#include <nengine.h>
#include <sglib.h>
#include <SDL_opengl.h>
#include <imgui_impl_sdl2.h>

#include "../imgui/imguiLayer.h"

namespace ns::editor
{

SDLWindow::SDLWindow(AppContext appContext, SystemContext sysContext)
    : appContext_(appContext), sysContext_(sysContext)
{
    switch(sysContext_.gpuEnv)
    {
        default:
        {
            initGL();
        }
    };

    imguiLayer_ = std::make_unique<ImguiLayer>(static_cast<void*>(this), sysContext_);
}

SDLWindow::~SDLWindow()
{
    SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(handle_);
	SDL_Quit();

    imguiLayer_.reset();
}

void SDLWindow::initGL()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        auto error = SDL_GetError();
        SG_LOG_CRITICAL("SDL INIT ERROR {}", error);
    }

    // Set GL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Create window with graphics context
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Create Window
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	handle_ = SDL_CreateWindow(appContext_.title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, appContext_.width, appContext_.height, windowFlags);
    if(handle_ == nullptr)
    {
        SG_LOG_CRITICAL("WINDOW INIT ERROR {}", SDL_GetError());
    }

    // Set GL Context
    context_ = SDL_GL_CreateContext(handle_);
    SDL_GL_MakeCurrent(handle_, context_);
    // SDL_GL_SetSwapInterval(1); // Enable vsync
}

void ns::editor::SDLWindow::processEvent(SystemIO& io)
{
    SDL_Event event;
    bool& done = io.done;

    while(!done)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(handle_))
                done = true;
        }
        if (SDL_GetWindowFlags(handle_) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }
        break;
    }
}


}	 // namespace ns::editor
