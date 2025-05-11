#include "imguiSceneWindow.h"
#include <imgui.h>

namespace ns::editor
{

ImVec2 ResToImVec2(const ns::Resolution& res)
{
    return ImVec2{static_cast<float>(res.width), static_cast<float>(res.height)};
}

void ImguiSceneWindow::draw()
{
    ImGuiWindowFlags sceneWindowFlags = sceneWindowFlags_;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
    {
        if (ImGui::Begin(context_.title.c_str(), 0, sceneWindowFlags | ImGuiWindowFlags_NoScrollbar) && context_.getImage && context_.getImage() != 0)
        {
            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
            ImVec2 beforePanelSize = ResToImVec2(context_.resolution) ;
            ImGui::ImageWithBg(context_.getImage(), beforePanelSize, ImVec2{0, 1}, ImVec2{1, 0});

            // resize callback
            auto width = static_cast<uint32_t>(viewportPanelSize.x);
            auto height = static_cast<uint32_t>(viewportPanelSize.y);
            if((context_.resolution.width != width || context_.resolution.height != height) && context_.resizeCallback)
            {
                context_.resolution = ns::Resolution{.height=height, .width=width};
                context_.resizeCallback(context_.resolution);
            }
        }
        ImGui::End();
    }
	ImGui::PopStyleVar();
}

}	 // namespace ns::editor