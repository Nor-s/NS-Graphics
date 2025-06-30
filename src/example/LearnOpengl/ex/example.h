#ifndef _LEARN_GL_EXAMPLE_H_
#define _LEARN_GL_EXAMPLE_H_

#include <cmath>

#include <core/gpu/gl/glGeometry.h>
#include <core/gpu/gl/glShader.h>
#include <core/gpu/gl/glBuffer.h>
#include <common/common.h>
#include <editor/app.h>
#include <imgui.h>
#include <editor/imgui/imguiComponents.h>

#include <nengine.h>

struct ExEntity
{
	std::unique_ptr<ns::GlGeometry> cube = nullptr;
	ns::Transform transform;
};

class Example
{
public:
	virtual ~Example()
	{
		inputController_.reset();
	}
	virtual const std::string& toString() = 0;
	virtual void destroy(){};
    virtual void content()=0;
	virtual bool update(double deltaTime)
	{
		return false;
	}
	virtual void drawUIWidgets(){}
	virtual void drawUIWindows(){}
	ns::InputController* getInputController()
	{
		return inputController_.get();
	}

protected:
	std::unique_ptr<ns::InputController> inputController_;
};

#endif