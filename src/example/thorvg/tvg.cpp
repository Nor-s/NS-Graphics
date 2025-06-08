/**
 *	reference: thorvg/examples/Example.h
 */
#include "tvg.h"

#include <editor/window/SDLWindow.h>
#include <editor/imgui/imguiSceneWindow.h>

#include <memory>
#include <string>
#include <iostream>

#include "imguiTvgWindow.h"
#include "scene/tvgexScene.h"

using namespace ns::editor;
using namespace std;

namespace tvgex
{

TVG::TVG()
{
}

TVG::~TVG()
{
}

void TVG::initBegin()
{
	int threadCount = 1;
	if (!verify(tvg::Initializer::init(threadCount), "Failed to init ThorVG engine"))
	{
		NS_ERROR("INIT_BEGIN");
		return;
	}
}
void TVG::initEnd()
{
	auto mainScene = std::make_unique<TvgexScene>((void*)sdlWindow_->getGLContext());
	mainScene_ = mainScene.get();
	sceneList_.push_back(std::move(mainScene));
}

void TVG::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiTVGWindow>(this));
	sdlWindow_->addImguiModule(std::make_unique<ImguiSceneWindow>(
		ImguiSceneWindow::Context{
			.sceneId=0,
			.title="main",
			.resolution=mainScene_->getResolution()
		}
	));
}

TvgexScene* TVG::getMainScene()
{
	return mainScene_;
}


}	 // namespace tvgex