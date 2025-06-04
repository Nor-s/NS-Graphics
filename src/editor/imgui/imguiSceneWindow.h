#ifndef _NS_GRAPHICS_EDITOR_IMGUI_IMGUI_SCENE_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_IMGUI_SCENE_H_

#include "imguiModule.h"
#include "core/common/common.h"

#include <string>

namespace ns::editor
{

class Scene;

class ImguiSceneWindow : public IImguiModule
{
public:
	struct Context
	{
		int sceneId = 0;
		std::string title;
		bool bIsShow = true;
		bool bIsFocus = false;
		ns::Resolution resolution;
		void (*resizeCallback)(int, const ns::Resolution&) = nullptr;
		uint64_t (*getImage)(int) = nullptr;
		void (*changeFocus)(int, bool) = nullptr;
	};

public:
	ImguiSceneWindow(const Context& context) : context_(context)
	{
	}
	~ImguiSceneWindow() = default;
	virtual void draw() override;

private:
	Context context_;
	int sceneWindowFlags_ = 0;
};
}	 // namespace ns::editor

#endif