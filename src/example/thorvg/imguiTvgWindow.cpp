#include "imguiTvgWindow.h"
#include <imgui.h>

#include "tvg.h"
#include "scene/tvgexScene.h"

namespace tvgex
{

using Examples = std::vector<std::unique_ptr<example::Example>>;

ImguiTVGWindow::ImguiTVGWindow(TVG* app) : app_(app)
{
}

void ImguiTVGWindow::draw()
{
	static int itemCurrent = 0;
	static const char* title = "setting";
	if (ImGui::Begin(title))
	{
		if (app_)
		{
			int beforeItem = itemCurrent;
			const Examples& examples = app_->getMainScene()->getExamples();
			ImGui::Combo(
				"examples", &itemCurrent,
				[](void* data, int n) { return ((const Examples*) data)->at(n)->toString().c_str(); },
				(void*) (&examples), examples.size());
			if (beforeItem != itemCurrent)
			{
				app_->getMainScene()->setExample(itemCurrent);
			}
		}
		ImGui::Separator();
		app_->getMainScene()->drawExampleUIWidgets();
	}
	ImGui::End();
	app_->getMainScene()->drawExampleUIWindows();
}

}	 // namespace tvgex