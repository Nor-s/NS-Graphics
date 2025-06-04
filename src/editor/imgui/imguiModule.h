#ifndef _NS_GRAPHICS_EDITOR_IMGUI_MODULE_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_MODULE_H_

namespace ns::editor
{
class ImguiLayer;

class IImguiModule
{
public:
	virtual ~IImguiModule() = default;
	virtual void draw() = 0;

protected:
	friend class ImguiLayer;
	ImguiLayer* parent_ = nullptr;
};

}	 // namespace ns::editor

#endif
