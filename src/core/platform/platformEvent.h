#ifndef _NS_GRAPHICS_CORE_PLATFORM_EVENT_H_
#define _NS_GRAPHICS_CORE_PLATFORM_EVENT_H_

#include "../common/nsVector.h"

namespace ns
{

struct SystemIO
{
	bool done = false;
	double deltaTime = 0.0;
	double globalTime = 0.0;
	Vec2 mousePos = Vec2(0.0f, 0.0f);
};

}	 // namespace ns

#endif