#ifndef _LEARN_GL_H_
#define _LEARN_GL_H_

#include <editor/app.h>
#include "ex/example.h"

class LearnGL : public ns::editor::App
{
public:
	using Examples = std::vector<std::unique_ptr<Example>>;

	~LearnGL();

	const Examples& getExamples()
	{
		return examples_;
	}
	void setExample(size_t idx);
	void drawExampleUIWidgets();
	void drawExampleUIWindows();

protected:
	virtual void initEnd() override final;
	virtual void addImguiModule() override final;
	virtual void draw() override final;
	virtual void initDefaultInputController() override final;

private:
	Examples examples_;
	size_t currentExampleIndex_ = 0;
};

#endif