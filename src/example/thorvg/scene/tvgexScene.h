#ifndef _TVGEX_SCENE_TVGEX_SCENE_H_
#define _TVGEX_SCENE_TVGEX_SCENE_H_

#include "../ex/ex00_shape.h"
#include "../ex/ex01_scene.h"
#include "../ex/ex02_update.h"
#include "../ex/ex03_region.h"
#include <editor/window/SDLWindow.h>
#include "../tvg.h"
#include <nengine.h>

namespace tvgex
{

using Examples = std::vector<std::unique_ptr<example::Example>>;

class TvgexScene : public ns::Scene
{
public:
	TvgexScene(void* context)
    : ns::Scene(), context_(context)
	{
	}
	virtual ~TvgexScene()
	{
		if (canvas_)
			delete (canvas_);
	}
	virtual void init(const ns::Resolution& res) override
	{
        ns::Scene::init(res);
		auto* glCanvas = tvg::GlCanvas::gen();
		canvas_ = glCanvas;


		examples_.emplace_back(std::make_unique<example::EX03_Region>());
		examples_.emplace_back(std::make_unique<example::EX02_Update>());
		examples_.emplace_back(std::make_unique<example::EX01_Scene>());
		examples_.emplace_back(std::make_unique<example::EX00_Shape>());

		static_cast<tvg::GlCanvas*>(canvas_)->target(context_, getRenderId(), res.width, res.height, tvg::ColorSpace::ABGR8888S);

		setExample(0);
	}
	virtual void resize(const ns::Resolution& res) override
	{
		ns::Scene::resize(res);
		static_cast<tvg::GlCanvas*>(canvas_)->target(context_, getRenderId(), res.width, res.height, tvg::ColorSpace::ABGR8888S);
		examples_[currentExample_]->resize(res);
	}

	virtual void draw() override
	{
		if (verify(canvas_->draw(), "TVG Draw Error"))
		{
			verify(canvas_->sync(), "TVG Sync Error");
		}
	}
	virtual void onUpdate() override
	{
		examples_[currentExample_]->update(canvas_, ns::editor::App::GetIO().deltaTime);
	}
    const Examples& getExamples()
    {
        return examples_;
    }
	void setExample(size_t index)
	{
		NS_LOG("SET_EXAMPLE");
		auto res = getResolution();

		currentExample_ = index;

		// init && initiate the first rendering
		if (!examples_[currentExample_]->content(canvas_, res.width, res.height))
		{
			NS_ERROR("SET_EXAMPLE");
		}
		NS_INFO("ok SET_EXAMPLE");
		r_inputController_ = examples_[currentExample_]->getInputController();
	}

	void drawExampleUIWidgets()
	{
		examples_[currentExample_]->drawUIWidgets();
	}

	void drawExampleUIWindows()
	{
		examples_[currentExample_]->drawUIWindows();
	}

private:
	void* context_;
	tvg::Canvas* canvas_ = nullptr;
	Examples examples_;
	size_t currentExample_ = 0;
};

}	 // namespace tvgex

#endif