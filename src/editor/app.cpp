#include "app.h"

#include <nengine.h>
#include "imgui/imguiLayer.h"
#include "window/SDLWindow.h"

#include "imgui/imguiWindow.h"
#include "imgui/imguiTextEditor.h"

#include <core/input/inputController.h>

namespace ns::editor
{
App* App::g_app = nullptr;

void App::SetCurrentInputController(ns::InputController* controller)
{
	if(controller == g_app->currentInputController_)
		return;
	g_app->sdlWindow_->resetInputState();
	g_app->currentInputController_ = controller;
}

void App::initDefaultInputController()
{
	defaultInputController_ = std::make_unique<InputController>();
	defaultInputController_->bindAction(InputAction{InputType::MOUSE_LEFT_DOWN}, InputTrigger::Started, [](const InputValue& value){
		auto v = value.get<ns::Vec3>();
		NS_INFO("drag start: x:{} y:{}", v.x, v.y);
	});
	defaultInputController_->bindAction(InputAction{InputType::MOUSE_LEFT_DOWN}, InputTrigger::Ended, [](const InputValue& value){
		auto v = value.get<ns::Vec3>();
		NS_INFO("drag END : x:{} y:{}", v.x, v.y);
	});
}

App::App()
{
	g_app = this;
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

InputController& App::getMutableInputController()
{
	if(currentInputController_ == nullptr)
	{
		return *defaultInputController_;
	}

	return *currentInputController_;
}

void App::initWindow()
{
	if (sysContext_.windowEnv == WindowEnv::SDL2)
	{
		sdlWindow_ = std::make_unique<SDLWindow>(appContext_, sysContext_);
	}
	initDefaultInputController();
}

}	 // namespace ns::editor