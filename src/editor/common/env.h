#ifndef _NS_GRAPHICS_EDITOR_ENV_H_
#define _NS_GRAPHICS_EDITOR_ENV_H_

#include <type_traits>
#include <string>

namespace ns::editor
{
enum WindowEnv : uint8_t
{
	SDL2 = 0x1,
};
enum GPUEnv : uint8_t
{
	OPENGL = 0x1,
	OPENGL_ES = 0x2,
};
struct AppContext
{
	std::string title = "";
	uint32_t width = 800;
	uint32_t height = 800;
	bool bIsDocMode = true;
};
struct SystemContext
{
	WindowEnv windowEnv = WindowEnv::SDL2;
	GPUEnv gpuEnv = GPUEnv::OPENGL_ES;
};
}	 // namespace ns::editor

#endif
