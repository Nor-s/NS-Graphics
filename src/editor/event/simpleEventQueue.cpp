#include "simpleEventQueue.h"

namespace ns::editor
{

void SimpleEventQueue::push(std::unique_ptr<Event> event) 
{
    events_.push_back(std::move(event));
}

void SimpleEventQueue::processEvent()
{
    for(auto& event: events_)
    {
        event->execute();
        event.reset();
    }
    events_.clear();
}

}