#include "app.h"

#include <nengine.h>		
#include "imgui/imguiLayer.h"
#include "window/SDLWindow.h"

namespace ns::editor
{

App::App(){

}

App::~App()
{
}

void App::run()
{
	SystemIO context;
	while(!context.done)
	{
		sdlWindow_->processEvent(context);
	}
}

void App::initWindow()
{
	if (sysContext_.windowEnv == WindowEnv::SDL2)
	{
		sdlWindow_ = std::make_unique<SDLWindow>(appContext_, sysContext_);
	}
}

}	 // namespace ns::editor