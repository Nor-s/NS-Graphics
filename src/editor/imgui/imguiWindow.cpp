#include "imguiWindow.h"

#include <imgui.h>

namespace ns::editor
{

void ImguiWindow::draw()
{
    ImGui::Begin(context_.title.data(), &context_.bIsShow);
    ImGui::End();
}

}
