#ifndef _NS_GRAPHICS_EDITOR_APP_H_
#define _NS_GRAPHICS_EDITOR_APP_H_

#include <string>
#include <memory>
#include "common/env.h"

namespace ns::editor
{

class SDLWindow;

class App
{
public:
    App();
    ~App();

	void init(AppContext appContext, SystemContext systemContext)
	{
        appContext_ = std::move(appContext);
        sysContext_ = std::move(systemContext);
        initWindow();
	}
	virtual void run();

private:
    virtual void initWindow();

private:
    AppContext appContext_;
    SystemContext sysContext_;

    std::unique_ptr<SDLWindow> sdlWindow_;
};

}	 // namespace ns::editor

#endif