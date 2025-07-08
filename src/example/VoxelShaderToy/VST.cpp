#include "VST.h"

#include <nengine.h>
#include <editor/window/SDLWindow.h>

#include <editor/imgui/imguiWindow.h>
#include <editor/imgui/imguiSceneWindow.h>
#include <editor/imgui/imguiTextEditor.h>

#include "Scene/Entity/box.h"
#include "Scene/mainScene.h"

using namespace ns::editor;

namespace vst
{

void VST::initEnd()
{
	sceneList_.push_back(std::make_unique<MainScene>());
}

void VST::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiTextEditor>());
	sdlWindow_->addImguiModule(std::make_unique<ImguiSceneWindow>(ImguiSceneWindow::Context{
		.title="scene",
		.sceneId=0,
		.resolution = sceneList_[0]->getResolution()
	}));
}

}	 // namespace vst