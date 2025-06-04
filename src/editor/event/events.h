#ifndef _NS_GRAPHICS_EDITOR_EVENT_EVENTS_H_
#define _NS_GRAPHICS_EDITOR_EVENT_EVENTS_H_

#include <core/common/common.h>

namespace ns::editor
{

class Event
{
public:
    Event() = default;
    virtual ~Event() = default;
	virtual void execute() = 0;
};

class SceneRenderTargetResizeEvent : public Event
{
public:
	SceneRenderTargetResizeEvent(int sceneId, const ns::Resolution& resolution)
		: sceneId_(sceneId), resolution_(resolution)
	{
	}
    ~SceneRenderTargetResizeEvent() = default;
	void execute() override;

private:
	int sceneId_{};
	ns::Resolution resolution_{};
};

class SceneFocusEvent : public Event
{
public:
    SceneFocusEvent(int sceneId, bool bIsFocus)
		: sceneId_(sceneId), bIsFocus_(bIsFocus)
	{
	}
    ~SceneFocusEvent() = default;
    void execute() override;

private:
	int sceneId_{};
    bool bIsFocus_{false};
};

}	 // namespace ns::editor

#endif