#include "VST.h"

#include <nengine.h>
#include <editor/window/SDLWindow.h>

#include <editor/imgui/imguiWindow.h>
#include <editor/imgui/imguiSceneWindow.h>
#include <editor/imgui/imguiTextEditor.h>

using namespace ns::editor;

namespace vst
{

void VST::initEnd()
{
	sceneList_.push_back(std::make_unique<ns::Scene>());
	sceneList_[0]->init(appContext_.res);
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