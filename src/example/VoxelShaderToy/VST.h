#ifndef _VST_VST_H_
#define _VST_VST_H_

#include <editor/app.h>
#include <core/gpu/gl/glRenderTarget.h>

namespace vst
{

class VST : public ns::editor::App
{
public:
	VST() = default;
	~VST() = default;

protected:
	virtual void initEnd() override final;
	virtual void addImguiModule() override final;
};

}	 // namespace vst

#endif