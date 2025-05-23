/**
 *	reference: thorvg/examples/Example.h
 */
#include "tvg.h"

#include <editor/window/SDLWindow.h>

#include <string>
#include <iostream>

#include "ex/ex00_shape.h"
#include "ex/ex01_scene.h"
#include "ex/ex02_update.h"
#include "imguiTvgWindow.h"

using namespace ns::editor;
using namespace std;
using namespace tvg;

namespace tvgex
{

TVG::TVG()
{
}

TVG::~TVG()
{
	if (canvas_)
		delete (canvas_);
}

void TVG::initBegin()
{
	NS_LOG("INIT_BEGIN");

	int threadCount = 1;
	if (!verify(Initializer::init(threadCount), "Failed to init ThorVG engine"))
	{
		NS_ERROR("INIT_BEGIN");
		return;
	}

	NS_INFO("ok INIT_BEGIN");
}

void TVG::initEnd()
{
	NS_LOG("INIT_END");

	auto* glCanvas = GlCanvas::gen();
	glCanvas->target(sdlWindow_->getGLContext(), 0, appContext_.res.width, appContext_.res.height, ColorSpace::ABGR8888S);
	canvas_ = glCanvas;

	examples_.emplace_back(std::make_unique<example::EX00_Shape>());
	examples_.emplace_back(std::make_unique<example::EX01_Scene>());
	examples_.emplace_back(std::make_unique<example::EX02_Update>());

	setExample(0);
	NS_INFO("ok INIT_END");
}

void TVG::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiTVGWindow>(this));
}

void TVG::predraw()
{
	
}
void TVG::draw()
{
	examples_[currentExample_]->update(canvas_, io_.deltaTime);

	// todo: add needDraw Logic
	if (verify(canvas_->draw(true), "TVG Draw Error"))
	{
		verify(canvas_->sync(), "TVG Sync Error");
		return;
	}
}

void TVG::postdraw()
{
}

bool TVG::setExample(size_t index)
{
	NS_LOG("SET_EXAMPLE");
	currentExample_ = index;

	// todo: resize width, height;
	auto width = appContext_.res.width;
	auto height = appContext_.res.height;

	// init && initiate the first rendering
	if (!examples_[currentExample_]->content(canvas_, width, height))
	{
		NS_ERROR("SET_EXAMPLE");
		return false;
	}
	NS_INFO("ok SET_EXAMPLE");
}

void TVG::drawExampleUIWidgets()
{
	examples_[currentExample_]->drawUIWidgets();
}

void TVG::drawExampleUIWindows()
{
	examples_[currentExample_]->drawUIWindows();
}

}	 // namespace tvgex