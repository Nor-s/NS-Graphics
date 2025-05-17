#include "imguiComponents.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <imgui.h>

namespace ImGuiEx 
{
bool DragFPropertyXYZ(const char* label,
					  float* value,
					  float step,
					  float min,
					  float max,
					  const char* format,
					  const std::string& help_message,
					  int num)
{
	bool is_value_changed = false;
	ImGui::PushID(label);
	ImGui::Columns(2, nullptr, false);
	ImGui::SetColumnWidth(0, 90.0f);

	ImGui::Text(label);
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(num, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f});

	const char* button_labels[] = {"X", "Y", "Z", "W"};
	const char* drag_labels[] = {"##x", "##y", "##z", "##w"};

	for (int i = 0; i < num; i++)
	{
		auto button_color = ImVec4{0.0f, 0.0f, 0.0f, 0.5f};
		auto framebg_color = ImVec4{0.4f, 0.4f, 0.4f, 0.1f};
		auto framebg_hovered_color = ImVec4{0.4f, 0.4f, 0.4f, 0.7f};
		auto framebg_active_color = ImVec4{0.5f, 0.5f, 0.5f, 1.0f};

		if (i == 0)
			button_color.x = framebg_hovered_color.x = framebg_active_color.x = framebg_color.x = 0.9f;
		else if (i == 1)
			button_color.y = framebg_hovered_color.y = framebg_active_color.y = framebg_color.y = 0.9f;
		else if (i == 2)
			button_color.z = framebg_hovered_color.z = framebg_active_color.z = framebg_color.z = 0.9f;

		ImGui::PushStyleColor(ImGuiCol_Button,
							  button_color);	// IM_COL32(button_color.r * 255, button_color.g * 255,
												// button_color.b * 255, button_color.a * 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
							  button_color);	// IM_COL32(button_color.r * 255, button_color.g * 255,
												// button_color.b * 255, button_color.a * 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive,
							  button_color);	// IM_COL32(button_color.r * 255, button_color.g * 255,
												// button_color.b * 255, button_color.a * 255));
		ImGui::PushStyleColor(
			ImGuiCol_FrameBgActive,
			(framebg_active_color));	// IM_COL32(framebg_active_color.r * 255, framebg_active_color.g * 255,
										// framebg_active_color.b * 255, framebg_active_color.a * 255));
		ImGui::PushStyleColor(
			ImGuiCol_FrameBgHovered,
			(framebg_hovered_color));	 // IM_COL32(framebg_hovered_color.r * 255, framebg_hovered_color.g * 255,
										 // framebg_hovered_color.b * 255, framebg_hovered_color.a * 255));
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
		ImGui::Button(button_labels[i]);
		ImGui::PopStyleColor(1);

		ImGui::SameLine();
		is_value_changed |= ImGui::DragFloat(drag_labels[i], &value[i], step, min, max, format);
		ImGui::PopItemWidth();
		if (i != num)
		{
			ImGui::SameLine();
		}
		ImGui::PopStyleColor(5);
	}

	ImGui::PopStyleVar();
	ImGui::Columns(1);

	ImGui::PopID();

	return is_value_changed;
}

bool DragPropertyXYZ(const char* label,
					 float* value,
					 float step,
					 float min,
					 float max,
					 const std::string& help_message)
{
	return DragFPropertyXYZ(label, value, step, min, max, "%.3f", help_message);
}
}