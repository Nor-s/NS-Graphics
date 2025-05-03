#ifndef _VST_VST_H_
#define _VST_VST_H_

#include <editor/app.h>

namespace vst
{

class VST :public ns::editor::App
{

protected:
    virtual void addImguiModule() override final;

};

}

#endif