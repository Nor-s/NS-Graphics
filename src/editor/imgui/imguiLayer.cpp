#include "imguiLayer.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "../window/SDLWindow.h"
#include <SDL_opengl.h>
namespace ns::editor
{
ImguiLayer::ImguiLayer(void* window, SystemContext sysContext) : context_(sysContext)
{
	init();
	if (context_.gpuEnv == GPUEnv::OPENGL && context_.windowEnv == WindowEnv::SDL2)
	{
		initSDL2OpenGL(window);
	}
}

ImguiLayer::~ImguiLayer()
{
	if (context_.gpuEnv == GPUEnv::OPENGL)
	{
		ImGui_ImplOpenGL3_Shutdown();
	}
	if (context_.windowEnv == WindowEnv::SDL2)
	{
		ImGui_ImplSDL2_Shutdown();
	}
	ImGui::DestroyContext();
}

void ImguiLayer::predraw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}
void ImguiLayer::draw()
{
	for(auto& module: modules_)
	{
		module->draw();
	}
}
void ImguiLayer::postdraw()
{
    ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this
	// code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

void ImguiLayer::init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void) io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	 // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	 // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		 // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		 // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
}

void ImguiLayer::initSDL2OpenGL(void* window)
{
	r_window_ = static_cast<SDLWindow*>(window);
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(r_window_->getHandle(), r_window_->getGLContext());
	ImGui_ImplOpenGL3_Init();
}

void ImguiLayer::addModule(std::unique_ptr<IImguiModule> module)
{
	modules_.emplace_back(std::move(module));
}

}	 // namespace ns::editor