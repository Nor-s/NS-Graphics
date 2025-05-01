#include "app.h"

#include <nengine.h>		
#include "imgui/imguiLayer.h"
#include "window/SDLWindow.h"

#include "imgui/imguiWindow.h"
#include "imgui/imguiTextEditor.h"

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
		sdlWindow_->predraw(context);
		sdlWindow_->draw(context);
		sdlWindow_->postdraw(context);
	}
}

void App::initWindow()
{
	if (sysContext_.windowEnv == WindowEnv::SDL2)
	{
		sdlWindow_ = std::make_unique<SDLWindow>(appContext_, sysContext_);
	}

	sdlWindow_->addImguiModule(std::make_unique<ImguiWindow>(ImguiWindow::Context{
		.title="preview"
	}));
	sdlWindow_->addImguiModule(std::make_unique<ImguiWindow>(ImguiWindow::Context{
		.title="scene"
	}));
	sdlWindow_->addImguiModule(std::make_unique<ImguiTextEditor>());
}

}	 // namespace ns::editor