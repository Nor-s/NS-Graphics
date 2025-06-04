#include "imguiSceneWindow.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "imguiLayer.h"
#include "../app.h"
#include "../event/events.h"

namespace ns::editor
{

ImVec2 ResToImVec2(const ns::Resolution& res)
{
	return ImVec2{static_cast<float>(res.width), static_cast<float>(res.height)};
}

ImguiSceneWindow::ImguiSceneWindow(const Context& context)
	: context_(context)
{
	if(context_.getImage == nullptr)
	{
		context_.getImage = [](int sceneId) -> uint64_t
		{
			return App::GetSceneImage(sceneId);
		};
	}
	if(context_.resizeCallback == nullptr)
	{
		context_.resizeCallback = [](int sceneId, const ns::Resolution& resolution)
		{
			App::PushEvent<SceneRenderTargetResizeEvent>(sceneId, resolution);
		};
	}
	if(context_.changeFocusCallback == nullptr)
	{
		context_.changeFocusCallback = [](int sceneId, bool bIsFocus)
		{
			App::PushEvent<SceneFocusEvent>(sceneId, bIsFocus);
		};
	}
}

void ImguiSceneWindow::draw()
{
	auto setMouseOffset = [this]()
	{
		if(parent_ == nullptr) return;
		auto cursorStartPos = ImGui::GetCursorStartPos();
		auto windowPos = ImGui::GetWindowPos();
		auto mousePos = ImGui::GetMousePos();
		auto offsetX = -(windowPos.x + cursorStartPos.x);
		auto offsetY = -(windowPos.y + cursorStartPos.y);
		parent_->setMouseOffset({offsetX, offsetY});
	};

	ImGuiWindowFlags sceneWindowFlags = sceneWindowFlags_;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
	{
		if (ImGui::Begin(context_.title.c_str(), 0, sceneWindowFlags | ImGuiWindowFlags_NoScrollbar) &&
			context_.getImage && context_.getImage(context_.sceneId) != 0)
		{
			// draw image
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			ImVec2 beforePanelSize = ResToImVec2(context_.resolution);
			ImGui::ImageWithBg(context_.getImage(context_.sceneId), beforePanelSize, ImVec2{0, 1}, ImVec2{1, 0});

			// resize callback
			auto width = static_cast<uint32_t>(viewportPanelSize.x);
			auto height = static_cast<uint32_t>(viewportPanelSize.y);
			if ((context_.resolution.width != width || context_.resolution.height != height) && context_.resizeCallback)
			{
				context_.resolution = ns::Resolution{.height = height, .width = width};
				context_.resizeCallback(context_.sceneId, context_.resolution);
			}

			// focused callback
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			bool bIsFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max);
			if(context_.changeFocusCallback != nullptr && bIsFocused != context_.bIsFocus)
			{
				context_.bIsFocus = bIsFocused;
				context_.changeFocusCallback(context_.sceneId, bIsFocused);
			}
			if(bIsFocused) setMouseOffset();
		}
		ImGui::End();
	}
	ImGui::PopStyleVar();
}


}	 // namespace ns::editor