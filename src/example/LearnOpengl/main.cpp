#include <iostream>
#include <nengine.h>
#include "learnGL.h"

using namespace ns::editor;

int main()
{
	ns::Logger::SetLogPrefix("LearnGL");

	App* app = new LearnGL;
	auto appContext = AppContext{.title = "LearnGL", .res = ns::Resolution{.width = 800, .height = 800}, .bIsDocMode=false};
	auto systemContext = SystemContext{
		.windowEnv = WindowEnv::SDL2,
		.gpuEnv = GPUEnv::OPENGL,
	};

	app->init(appContext, systemContext);
	app->run();

	delete app;
}