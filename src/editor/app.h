#ifndef _NS_GRAPHICS_EDITOR_APP_H_
#define _NS_GRAPHICS_EDITOR_APP_H_

#include <string>
#include <memory>
#include "common/env.h"
#include "platform/platformEvent.h"

namespace ns
{
class InputController;
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
	

public:
	App();
	virtual ~App();

	void init(AppContext appContext, SystemContext systemContext)
	{
		initBegin();
		appContext_ = std::move(appContext);
		sysContext_ = std::move(systemContext);
		initWindow();
		initEnd();
	}
	virtual void run();

protected:
	virtual void preProcessEvent() {};
	virtual void initBegin() {};
	virtual void initEnd() {};
	virtual void addImguiModule()
	{
	}
	virtual void predraw() {};
	virtual void draw()
	{
	}
	virtual void postdraw() {};
	virtual InputController& getMutableInputController();
	virtual void initDefaultInputController();

protected:
	std::unique_ptr<SDLWindow> sdlWindow_;
	AppContext appContext_;
	SystemContext sysContext_;
	SystemIO io_;
	std::unique_ptr<InputController> defaultInputController_;
	InputController* currentInputController_ = nullptr;

private:
	void initWindow();
};

}	 // namespace ns::editor

#endif