#include "learnGL.h"

#include <editor/window/SDLWindow.h>

#include <editor/imgui/imguiWindow.h>
#include <editor/imgui/imguiTextEditor.h>

#include "ex/ex00_shape.h"
#include "ex/ex01_transform.h"
#include "ex/ex02_coordinate.h"
#include "ex/ex03_basicLighting.h"

#include "imguiExampleWindow.h"

using namespace ns::editor;

LearnGL::~LearnGL()
{
	for(auto& example : examples_)
	{
		example.reset();
	}
	examples_.clear();
}

void LearnGL::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiExampleWindow>(this));
}

void LearnGL::initEnd()
{
	examples_.emplace_back(std::make_unique<Ex03_BasicLighting>());
	examples_.emplace_back(std::make_unique<Ex02_Coordinate>());
	examples_.emplace_back(std::make_unique<Ex01_Transform>());
	examples_.emplace_back(std::make_unique<Ex00_Shape>());

	setExample(0);
}
void LearnGL::draw()
{
	examples_[currentExampleIndex_]->update(io_.deltaTime);
}

void LearnGL::setExample(size_t idx)
{
	examples_[currentExampleIndex_]->destroy();
	currentExampleIndex_ = idx;
	examples_[currentExampleIndex_]->content();
}

void LearnGL::drawExampleUIWidgets()
{
	examples_[currentExampleIndex_]->drawUIWidgets();
}
void LearnGL::drawExampleUIWindows()
{
	examples_[currentExampleIndex_]->drawUIWindows();
}

void LearnGL::onWindowResize(const ns::Resolution& res)
{
	examples_[currentExampleIndex_]->onWindowResize(res);
}

void LearnGL::initDefaultInputController()
{
	defaultInputController_ = std::make_unique<ns::InputController>();
}