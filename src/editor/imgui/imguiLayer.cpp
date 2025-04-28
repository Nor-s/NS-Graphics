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
	static bool show_demo_window = true;
	static bool show_another_window = true;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGuiIO& io = ImGui::GetIO();
	(void) io;

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to
	// learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");	  // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");			  // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);	  // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);				// Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*) &clear_color);	// Edit 3 floats representing a color

		if (ImGui::Button(
				"Button"))	  // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}
	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window",
					 &show_another_window);	   // Pass a pointer to our bool variable (the window will have a closing
											   // button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	ImGui::Render();
	glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
				 clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}
void ImguiLayer::postdraw()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this
	// code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
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

}	 // namespace ns::editor