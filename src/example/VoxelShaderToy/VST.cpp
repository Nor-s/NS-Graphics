#include "VST.h"

#include <editor/window/SDLWindow.h>

#include <editor/imgui/imguiWindow.h>
#include <editor/imgui/imguiTextEditor.h>

using namespace ns::editor;


namespace vst
{

void VST::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiWindow>(ImguiWindow::Context{
		.title="preview"
	}));
	sdlWindow_->addImguiModule(std::make_unique<ImguiWindow>(ImguiWindow::Context{
		.title="scene"
	}));
	sdlWindow_->addImguiModule(std::make_unique<ImguiTextEditor>());
}

}	 // namespace vst