#include "app.h"

#include <core/input/inputController.h>
#include <nengine.h>

#include "window/SDLWindow.h"

#include "imgui/imguiLayer.h"
#include "imgui/imguiWindow.h"
#include "imgui/imguiTextEditor.h"

#include "event/simpleEventQueue.h"
#include "event/events.h"

namespace ns::editor
{
App* App::g_app = nullptr;

void App::SetCurrentInputController(ns::InputController* controller)
{
	if (controller == g_app->currentInputController_)
		return;
	g_app->sdlWindow_->resetInputState();
	g_app->currentInputController_ = controller;
}

uint64_t App::GetSceneImage(int sceneId)
{
	if(g_app == nullptr || 0 < sceneId || sceneId > g_app->sceneList_.size() )
	{
		return 0u;
	}
	return g_app->sceneList_[sceneId]->getSceneImage();
}
void App::SceneResize(int sceneId, const ns::Resolution& resolution)
{
	if( g_app == nullptr || 0 < sceneId || sceneId > g_app->sceneList_.size() )
	{
		return;
	}
	return g_app->sceneList_[sceneId]->resize(resolution);
}
void App::SetSceneFocus(int sceneId, bool bIsFocus)
{
	if( g_app == nullptr || 0 < sceneId || sceneId > g_app->sceneList_.size() )
	{
		return;
	}
	SetCurrentInputController(g_app->sceneList_[sceneId]->getInputController());
}

void App::initDefaultInputController()
{
	defaultInputController_ = std::make_unique<InputController>();
	defaultInputController_->bindAction(InputAction{InputType::MOUSE_LEFT_DOWN}, InputTrigger::Started,
										[](const InputValue& value)
										{
											auto v = value.get<ns::Vec3>();
											NS_INFO("drag start: x:{} y:{}", v.x, v.y);
										});
	defaultInputController_->bindAction(InputAction{InputType::MOUSE_LEFT_DOWN}, InputTrigger::Ended,
										[](const InputValue& value)
										{
											auto v = value.get<ns::Vec3>();
											NS_INFO("drag END : x:{} y:{}", v.x, v.y);
										});
}

void App::initEventController()
{
	eventController_ = std::make_unique<SimpleEventQueue>();
}

App::App()
{
	g_app = this;
}

App::~App()
{
}
void App::init(AppContext appContext, SystemContext systemContext)
{
	appContext_ = std::move(appContext);
	sysContext_ = std::move(systemContext);
	initBegin();
	initWindow();
	initDefaultInputController();
	initEventController();
	initEnd();

	initScene();
}
void App::run()
{
	addImguiModule();

	Timer timer;
	SystemIO& context = io_;
	while (!context.done)
	{
		preProcessEvent();
		eventController_->processEvent();
		sdlWindow_->processEvent(context);

		update();

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

void App::draw()
{
	for (auto& scene : sceneList_)
	{
		scene->onRender();
	}
}

InputController& App::getMutableInputController()
{
	if (currentInputController_ == nullptr)
	{
		return *defaultInputController_;
	}

	return *currentInputController_;
}

void App::update()
{
	for(auto& scene: sceneList_)
	{
		scene->onUpdate();
	}
}

void App::initWindow()
{
	if (sysContext_.windowEnv == WindowEnv::SDL2)
	{
		sdlWindow_ = std::make_unique<SDLWindow>(appContext_, sysContext_);
	}
}

void App::initScene()
{
	for(auto& scene: sceneList_)
	{
		scene->init(appContext_.res);
	}
}

}	 // namespace ns::editor