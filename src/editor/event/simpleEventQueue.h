#ifndef _NS_GRAPHICS_EDITOR_EVENT_SIMPLE_EVENT_QUEUE_H_
#define _NS_GRAPHICS_EDITOR_EVENT_SIMPLE_EVENT_QUEUE_H_

#include <vector>
#include "eventController.h"

namespace ns::editor
{

class SimpleEventQueue : public EventController
{
public:
    SimpleEventQueue() = default;
    ~SimpleEventQueue() = default;
    virtual void push(std::unique_ptr<Event> event) override;
    virtual void processEvent() override;

private:
    std::vector<std::unique_ptr<Event>> events_;
};

}	 // namespace ns::editor

#endif