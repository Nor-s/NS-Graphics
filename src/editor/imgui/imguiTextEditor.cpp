#include "imguiTextEditor.h"

#include <imgui.h>

namespace ns::editor
{
ImguiTextEditor::ImguiTextEditor()
{
    init();
}

void ImguiTextEditor::init()
{
	editor_.SetLanguageDefinition(lang_);
}

void ImguiTextEditor::draw()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags = ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar;
    int line=0, column=0;
	editor_.GetCursorPosition(line, column);
	ImGui::Begin("Text Editor Demo", nullptr, window_flags);
	ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Dark palette"))
				editor_.SetPalette(TextEditor::PaletteId::Dark);
			if (ImGui::MenuItem("Light palette"))
				editor_.SetPalette(TextEditor::PaletteId::Light);
			if (ImGui::MenuItem("Mariana palette"))
				editor_.SetPalette(TextEditor::PaletteId::Mariana);
			ImGui::EndMenu();
		}
    	ImGui::Text("line: %d column: %d  %s  %s", line + 1, column + 1
				, editor_.CanUndo() ? "*" : " ",
				editor_.GetLanguageDefinitionName());
		ImGui::EndMenuBar();
	}

	editor_.Render("TextEditor");
	ImGui::End();
}

}	 // namespace ns::editor