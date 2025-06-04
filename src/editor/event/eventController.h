#ifndef _NS_GRAPHICS_EDITOR_EVENT_EVENT_CONTROLLER_H_
#define _NS_GRAPHICS_EDITOR_EVENT_EVENT_CONTROLLER_H_

#include <memory>
#include "events.h"

namespace ns::editor
{

class EventController
{
public:
	EventController() = default;
	virtual ~EventController() = default;
	virtual void push(std::unique_ptr<Event> event) = 0;
	virtual void processEvent() = 0;
};

}	 // namespace ns::editor

#endif