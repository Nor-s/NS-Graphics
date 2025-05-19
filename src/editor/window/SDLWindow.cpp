#include "SDLWindow.h"

#include <nengine.h>
#include <SDL_opengl.h>
#include <imgui_impl_sdl2.h>

#include "../imgui/imguiLayer.h"

namespace ns::editor
{

SDLWindow::SDLWindow(const AppContext& appContext, const SystemContext& sysContext)
	: appContext_(appContext), sysContext_(sysContext)
{
	switch (sysContext_.gpuEnv)
	{
		default:
		{
			initGL();
		}
	};

	imguiLayer_ = std::make_unique<ImguiLayer>(static_cast<void*>(this), sysContext_);
	imguiLayer_->setDocMode(appContext_.bIsDocMode);
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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		auto error = SDL_GetError();
		NS_CRITICAL("SDL INIT ERROR {}", error);
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
	SDL_WindowFlags windowFlags =
		(SDL_WindowFlags) (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	handle_ = SDL_CreateWindow(appContext_.title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							   appContext_.res.width, appContext_.res.height, windowFlags);
	if (handle_ == nullptr)
	{
		NS_CRITICAL("WINDOW INIT ERROR {}", SDL_GetError());
	}

	// Set GL Context
	context_ = SDL_GL_CreateContext(handle_);
	SDL_GL_MakeCurrent(handle_, context_);
	// SDL_GL_SetSwapInterval(1); // Enable vsync
}

void SDLWindow::processEvent(SystemIO& io)
{
	SDL_Event event;
	bool& done = io.done;

	while (!done)
	{
		SDL_GL_SwapWindow(handle_);
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
				event.window.windowID == SDL_GetWindowID(handle_))
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

void SDLWindow::predraw(SystemIO& io)
{
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	glEnable(GL_DEPTH_TEST);  

	glViewport(0, 0, (int) appContext_.res.width, (int) appContext_.res.height);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
				 clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	imguiLayer_->predraw();
}
void SDLWindow::draw(SystemIO& io)
{
	imguiLayer_->draw();
}
void SDLWindow::postdraw(SystemIO& io)
{
	imguiLayer_->postdraw();
}
void SDLWindow::addImguiModule(std::unique_ptr<IImguiModule> module)
{
	imguiLayer_->addModule(std::move(module));
}

}	 // namespace ns::editor
