#include "learnGL.h"

#include <editor/window/SDLWindow.h>

#include <editor/imgui/imguiWindow.h>
#include <editor/imgui/imguiTextEditor.h>

#include "ex/ex00_shape.h"
#include "imguiExampleWindow.h"

using namespace ns::editor;

void LearnGL::addImguiModule()
{
	sdlWindow_->addImguiModule(std::make_unique<ImguiExampleWindow>(this));
}

void LearnGL::initEnd()
{
	examples_.emplace_back(std::make_unique<Ex00_Shape>());
	setExample(0);
}
void LearnGL::draw()
{
	examples_[currentExampleIndex_]->update(io_.deltaTime);
}

void LearnGL::setExample(size_t idx)
{
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