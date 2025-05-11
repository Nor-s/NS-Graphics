#ifndef _NS_GRAPHICS_EDITOR_IMGUI_IMGUI_SCENE_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_IMGUI_SCENE_H_

#include "imguiModule.h"
#include "core/common/common.h"

#include <string>

namespace ns::editor
{

class ImguiSceneWindow : public IImguiModule
{
public:
	struct Context
	{
		std::string title;
		bool bIsShow = true;
		ns::Resolution resolution;
		void (*resizeCallback)(const ns::Resolution&) = nullptr;
		uint64_t (*getImage)() = nullptr;
	};

public:
	ImguiSceneWindow(const Context& context) : context_(context)
	{
	}
	~ImguiSceneWindow() = default;
	virtual void draw() override;

private:
private:
	Context context_;
	int sceneWindowFlags_ = 0;
};
}	 // namespace ns::editor

#endif