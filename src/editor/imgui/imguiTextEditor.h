#ifndef _NS_GRAPHICS_EDITOR_IMGUI_TEXT_EDITOR_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_TEXT_EDITOR_H_

#include "imguiModule.h"
#include <textEditor/TextEditor.h>

namespace ns::editor
{
class ImguiTextEditor : public IImguiModule
{
public:
	ImguiTextEditor();
	~ImguiTextEditor() = default;
	virtual void draw() override;

private:
	void init();

private:
	TextEditor editor_;
	TextEditor::LanguageDefinitionId lang_ = TextEditor::LanguageDefinitionId::Lua;
};
}	 // namespace ns::editor

#endif
