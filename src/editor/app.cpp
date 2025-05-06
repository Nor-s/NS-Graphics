#include "app.h"

#include <nengine.h>
#include "imgui/imguiLayer.h"
#include "window/SDLWindow.h"

#include "imgui/imguiWindow.h"
#include "imgui/imguiTextEditor.h"

namespace ns::editor
{

App::App()
{
}

App::~App()
{
}

void App::run()
{
	Timer timer;
	SystemIO& context = io_;
	while (!context.done)
	{
		sdlWindow_->processEvent(context);

		sdlWindow_->predraw(context);
		predraw();

		sdlWindow_->draw(context);
		draw();

		sdlWindow_->postdraw(context);
		postdraw();

		context.deltaTime = timer.elapsed();
		context.globalTime = timer.duration();
	}
}

void App::initWindow()
{
	if (sysContext_.windowEnv == WindowEnv::SDL2)
	{
		sdlWindow_ = std::make_unique<SDLWindow>(appContext_, sysContext_);
	}
	addImguiModule();
}

}	 // namespace ns::editor