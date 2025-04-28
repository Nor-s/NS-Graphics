#include <iostream>
#include <sglib.h>
#include "app.h"

using namespace ns::editor;

int main()
{
	sglib::Logger::SetLogPrefix("NS-Graphics");

	auto app = App();
	auto appContext = AppContext{.title = "NS-Graphics", .width = 800, .height = 600};
	auto systemContext = SystemContext{
		.windowEnv = WindowEnv::SDL2,
		.gpuEnv = GPUEnv::OPENGL,
	};

	app.init(appContext, systemContext);
	app.run();
}