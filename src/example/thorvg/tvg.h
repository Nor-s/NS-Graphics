#ifndef _TVG_TVG_H_
#define _TVG_TVG_H_

#include <editor/app.h>
#include <memory>

#include "ex/example.h"

namespace tvgex
{
class TVG : public ns::editor::App
{
public:
	using Examples = std::vector<std::unique_ptr<example::Example>>;

public:
	TVG();
	~TVG();
	const Examples& getExamples()
	{
		return examples_;
	}
	bool setExample(size_t index);
	void drawExampleUIWidgets(); 
	void drawExampleUIWindows(); 

protected:
	virtual void initBegin() override final;
	virtual void initEnd() override final;
	virtual void addImguiModule() override final;
	virtual void predraw() override final;
	virtual void draw() override final;
	virtual void postdraw() override final;

private:
	tvg::Canvas* canvas_ = nullptr;
	Examples examples_;
	size_t currentExample_ = 0;
};

}	 // namespace tvgex

#endif