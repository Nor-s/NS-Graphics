#include "imguiTvgWindow.h"
#include <imgui.h>

#include "tvg.h"

namespace tvgex
{

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
			const TVG::Examples& examples = app_->getExamples();
			ImGui::Combo(
				"examples", &itemCurrent,
				[](void* data, int n) { return ((const TVG::Examples*) data)->at(n)->toString().c_str(); },
				(void*) (&examples), examples.size());
			if (beforeItem != itemCurrent)
			{
				app_->setExample(itemCurrent);
			}
		}
		ImGui::End();
	}
}

}	 // namespace tvgex