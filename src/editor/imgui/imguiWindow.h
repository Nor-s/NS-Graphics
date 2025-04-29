#ifndef _NS_GRAPHICS_EDITOR_IMGUI_WINDOW_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_WINDOW_H_

#include <string>
#include <vector>
#include "imguiModule.h"

namespace ns::editor
{

class ImguiWindow : public IImguiModule
{
public:
    struct Context
    {
        bool bIsShow = true;
        std::string title;
    };

public:
    ImguiWindow() = default;
    ImguiWindow(const Context& context)
        :context_(context)
    {
    }
    ~ImguiWindow() = default;
	virtual void draw() override;

private:
    Context context_;

};

}	 // namespace ns::eidtor

#endif
