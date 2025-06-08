#ifndef _TVG_TVG_H_
#define _TVG_TVG_H_

#include <nengine.h>
#include <editor/app.h>
#include <memory>

namespace tvgex
{
class TvgexScene;
class TVG : public ns::editor::App
{
public:
	TVG();
	~TVG();
	TvgexScene* getMainScene(); 

protected:
	virtual void initBegin() override final;
	virtual void initEnd() override final;
	virtual void addImguiModule() override final;

private:
	TvgexScene* mainScene_;
};

}	 // namespace tvgex

#endif