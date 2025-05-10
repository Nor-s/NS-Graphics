#include <iostream>
#include <nengine.h>
#include "VST.h"

using namespace ns::editor;
using namespace vst;

int main()
{
	ns::Logger::SetLogPrefix("NS-Graphics");

	App* app = new VST;
	auto appContext = AppContext{.title = "Voxel Shader Toy", .width = 800, .height = 800, .bIsDocMode=true};
	auto systemContext = SystemContext{
		.windowEnv = WindowEnv::SDL2,
		.gpuEnv = GPUEnv::OPENGL,
	};

	app->init(appContext, systemContext);
	app->run();

	delete app;
}