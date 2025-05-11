#include "imguiExampleWindow.h"
#include <imgui.h>

#include "learnGL.h"

ImguiExampleWindow::ImguiExampleWindow(LearnGL* app) : app_(app)
{
}

void ImguiExampleWindow::draw()
{
	static int itemCurrent = 0;
	static const char* title = "setting";
	if (ImGui::Begin(title))
	{
		if (app_)
		{
			int beforeItem = itemCurrent;
			const auto& examples = app_->getExamples();
			ImGui::Combo(
				"examples", &itemCurrent,
				[](void* data, int n) { return ((const LearnGL::Examples*) data)->at(n)->toString().c_str(); },
				(void*) (&examples), examples.size());
			if (beforeItem != itemCurrent)
			{
				app_->setExample(itemCurrent);
			}
		}
		ImGui::Separator();
		app_->drawExampleUIWidgets();
	}
	ImGui::End();
	app_->drawExampleUIWindows();
}
