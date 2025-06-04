#ifndef _NS_GRAPHICS_EDITOR_APP_H_
#define _NS_GRAPHICS_EDITOR_APP_H_

#include <string>
#include <memory>
#include "common/env.h"
#include <platform/platformEvent.h>
#include "event/eventController.h"

namespace ns
{
class InputController;
class Scene;
}

namespace ns::editor
{

class SDLWindow;

class App
{
	static App* g_app;

public:
	static const AppContext& GetAppContext()
	{
		return g_app->appContext_;
	}
	static InputController& GetMutableRefInputController()
	{
		return g_app->getMutableInputController();
	}

	static void SetCurrentInputController(InputController* inputController);

	static uint64_t GetSceneImage(int sceneId);
	static void SceneResize(int sceneId, const ns::Resolution& resolution);
	static void SetSceneFocus(int sceneId, bool bIsFocus);

	template <typename EventType, typename... Args>
	static void PushEvent(Args&&... args)
	{
		g_app->eventController_->push(std::make_unique<EventType>(std::forward<Args>(args)...));
	}

public:
	App();
	virtual ~App();

	void init(AppContext appContext, SystemContext systemContext);
	virtual void run();

protected:
	virtual void preProcessEvent() {};
	virtual void initBegin() {};
	virtual void initEnd() {};
	virtual void addImguiModule()
	{
	}
	virtual void predraw() {};
	virtual void draw();
	virtual void postdraw() {};
	virtual InputController& getMutableInputController();
	virtual void initDefaultInputController();
	virtual void initEventController();

protected:
	AppContext appContext_;
	SystemContext sysContext_;
	SystemIO io_;
	InputController* currentInputController_;
	std::unique_ptr<SDLWindow> sdlWindow_;
	std::unique_ptr<InputController> defaultInputController_;
	std::unique_ptr<EventController> eventController_ = nullptr;
	std::vector<std::unique_ptr<ns::Scene>> sceneList_;

private:
	void initWindow();
};

}	 // namespace ns::editor

#endif