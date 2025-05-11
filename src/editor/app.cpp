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
	addImguiModule();

	Timer timer;
	SystemIO& context = io_;
	while (!context.done)
	{
		preProcessEvent();
		sdlWindow_->processEvent(context);

		sdlWindow_->predraw(context);
		predraw();

		draw();
		sdlWindow_->draw(context);

		postdraw();
		sdlWindow_->postdraw(context);

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
}

}	 // namespace ns::editor