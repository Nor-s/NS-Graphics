#ifndef _NS_GRAPHICS_EDITOR_IMGUI_IMGUI_COMPONENTS_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_IMGUI_COMPONENTS_H_

#include <string>

namespace ImGuiEx
{

bool DragFPropertyXYZ(const char* label,
					  float* value,
					  float step = 0.01f,
					  float min = -1000.0f,
					  float max = 1000.0f,
					  const char* format = "%.2f",
					  const std::string& help_message = "",
					  int num = 3);
bool DragPropertyXYZ(const char* label,
					 float* value,
					 float step = 0.01f,
					 float min = -1000.0f,
					 float max = 1000.0f,
					 const std::string& help_message = "");

}	 // namespace ns::editor

#endif