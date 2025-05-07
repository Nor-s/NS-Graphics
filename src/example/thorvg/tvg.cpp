/**
 *	reference: thorvg/examples/Example.h
 */
#include "tvg.h"

#include <editor/window/SDLWindow.h>

#include <string>
#include <iostream>
#include <sglib.h>

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
	SG_LOG_LOG("INIT_BEGIN");

	int threadCount = 1;
	if (!verify(Initializer::init(threadCount), "Failed to init ThorVG engine"))
	{
		SG_LOG_ERROR("INIT_BEGIN");
		return;
	}

	SG_LOG_INFO("ok INIT_BEGIN");
}

void TVG::initEnd()
{
	SG_LOG_LOG("INIT_END");

	auto* glCanvas = GlCanvas::gen();
	glCanvas->target(sdlWindow_->getGLContext(), 0, appContext_.width, appContext_.height, ColorSpace::ABGR8888S);
	canvas_ = glCanvas;

	examples_.emplace_back(std::make_unique<example::EX01_Scene>());
	examples_.emplace_back(std::make_unique<example::EX02_Update>());

	setExample(0);
	SG_LOG_INFO("ok INIT_END");
}

void TVG::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiTVGWindow>(this));
}

void TVG::predraw()
{
	examples_[currentExample_]->update(canvas_, io_.globalTime);

	// todo: add needDraw Logic
	if (verify(canvas_->draw(true), "TVG Draw Error"))
	{
		verify(canvas_->sync(), "TVG Sync Error");
		return;
	}
}
void TVG::draw()
{
}

void TVG::postdraw()
{
}

bool TVG::setExample(size_t index)
{
	SG_LOG_LOG("SET_EXAMPLE");
	currentExample_ = index;

	// todo: resize width, height;
	auto width = appContext_.width;
	auto height = appContext_.height;

	// init && initiate the first rendering
	if (!examples_[currentExample_]->content(canvas_, width, height))
	{
		SG_LOG_ERROR("SET_EXAMPLE");
		return false;
	}
	SG_LOG_INFO("ok SET_EXAMPLE");
}

}	 // namespace tvgex