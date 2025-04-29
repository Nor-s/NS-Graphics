#ifndef _NS_GRAPHICS_EDITOR_IMGUI_MODULE_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_MODULE_H_

namespace ns::editor
{

class IImguiModule
{
public:
    virtual ~IImguiModule() = default;
    virtual void draw() = 0;
};

}	 // namespace ns::editor

#endif
