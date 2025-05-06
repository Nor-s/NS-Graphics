#include <iostream>
#include <sglib.h>
#include "tvg.h"

using namespace ns::editor;

int main()
{
	sglib::Logger::SetLogPrefix("NS-Graphics");

	auto* app = new tvgex::TVG;
	auto appContext = AppContext{.title = "Voxel Shader Toy", .width = 800, .height = 800, .bIsDocMode = false};
	auto systemContext = SystemContext{
		.windowEnv = WindowEnv::SDL2,
		.gpuEnv = GPUEnv::OPENGL,
	};

	app->init(appContext, systemContext);
	app->run();
}