#include <iostream>
#include <nengine.h>
#include "tvg.h"

using namespace ns::editor;

int main()
{
	ns::Logger::SetLogPrefix("TVG");

	auto* app = new tvgex::TVG;
	auto appContext = AppContext{.title = "TVG Examples", .width = 800, .height = 800, .bIsDocMode = false};
	auto systemContext = SystemContext{
		.windowEnv = WindowEnv::SDL2,
		.gpuEnv = GPUEnv::OPENGL,
	};

	app->init(appContext, systemContext);
	app->run();
}