#ifndef _VST_VST_H_
#define _VST_VST_H_

#include <editor/app.h>
#include <core/gpu/gl/glRenderTarget.h>

namespace vst
{

class Event
{
public:
	virtual void execute() = 0;
};

class SceneRenderTargetResizeEvent : public Event
{
public:
	SceneRenderTargetResizeEvent(int sceneId, const ns::Resolution& resolution)
		: sceneId_(sceneId), resolution_(resolution)
	{
	}
	void execute() override;

private:
	int sceneId_;
	ns::Resolution resolution_;
};

class VST : public ns::editor::App
{
public:
	static VST* g_vst;

	void pushEvent(std::unique_ptr<Event> event)
	{
		events_.push_back(std::move(event));
	}
	void initScene(const ns::Resolution& res);
	uint64_t getSceneImage(int sceneId);

protected:
	virtual void preProcessEvent() override final;
	virtual void initEnd() override final;
	virtual void draw() override final;
	virtual void addImguiModule() override final;

private:
	std::unique_ptr<ns::GlRenderTarget> sceneRenderTarget_;
	std::vector<std::unique_ptr<Event>> events_;
};

}	 // namespace vst

#endif