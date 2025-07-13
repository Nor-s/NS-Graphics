#ifndef _NS_GRAPHICS_EDITOR_IMGUI_TEXT_EDITOR_H_
#define _NS_GRAPHICS_EDITOR_IMGUI_TEXT_EDITOR_H_

#include "imguiModule.h"

#include <textEditor/TextEditor.h>
#include <string_view>
#include <string>
#include <functional>

namespace ns::editor
{
class ImguiTextEditor : public IImguiModule
{
public:
	struct Context
	{
		std::function<void(std::string_view)> typeCallback ;
		std::function<std::string()> getTextCallback;
	};
	ImguiTextEditor(const Context& context)
		: context_(context) 
	{
		init();
	}
	~ImguiTextEditor() = default;
	virtual void draw() override;

private:
	void init();

private:
	Context context_;
	TextEditor editor_;
	TextEditor::LanguageDefinitionId lang_ = TextEditor::LanguageDefinitionId::Lua;
};
}	 // namespace ns::editor

#endif
