#ifndef _TVG_TVG_IMGUI_TVG_WINDOW_H_
#define _TVG_TVG_IMGUI_TVG_WINDOW_H_

#include <imgui/imguiModule.h>

namespace tvgex
{

class TVG;

class ImguiTVGWindow : public ns::editor::IImguiModule
{
public:
	ImguiTVGWindow(TVG* app);
	~ImguiTVGWindow() = default;

	virtual void draw() override;

private:
	TVG* app_;
};

}	 // namespace tvgex

#endif