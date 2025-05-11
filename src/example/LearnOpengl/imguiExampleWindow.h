#ifndef _LEARN_GL_IMGUI_EXAMPLE_WINDOW_H_
#define _LEARN_GL_IMGUI_EXAMPLE_WINDOW_H_

#include <imgui/imguiModule.h>

class LearnGL;

class ImguiExampleWindow : public ns::editor::IImguiModule
{
public:
	ImguiExampleWindow(LearnGL* app);
	~ImguiExampleWindow() = default;

	virtual void draw() override;

private:
	LearnGL* app_;
};

#endif