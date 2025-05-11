#ifndef _LEARN_GL_EXAMPLE_H_
#define _LEARN_GL_EXAMPLE_H_

#include <nengine.h>

class Example
{
public:
	virtual const std::string& toString() = 0;
    virtual void content()=0;
	virtual bool update(double deltaTime)
	{
		return false;
	}
	virtual void drawUIWidgets(){}
	virtual void drawUIWindows(){}
};

#endif