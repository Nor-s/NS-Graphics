#include "imguiLayer.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "../window/SDLWindow.h"

namespace ns::editor
{
ImguiLayer::ImguiLayer(void* window, SystemContext sysContext)
    :context_(sysContext)
{
    init();
    if(context_.gpuEnv == GPUEnv::OPENGL && context_.windowEnv == WindowEnv::SDL2)
    {
        initSDL2OpenGL(window);
    }
}

ImguiLayer::~ImguiLayer()
{
    if(context_.gpuEnv == GPUEnv::OPENGL)
    {
        ImGui_ImplOpenGL3_Shutdown();
    }
    if(context_.windowEnv == WindowEnv::SDL2)
    {
        ImGui_ImplSDL2_Shutdown();
    }
    ImGui::DestroyContext();
}

void ImguiLayer::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

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
    SDLWindow* sdlWindow = static_cast<SDLWindow*>(window);
        // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(sdlWindow->getHandle(), sdlWindow->getGLContext());
    ImGui_ImplOpenGL3_Init();
}

}