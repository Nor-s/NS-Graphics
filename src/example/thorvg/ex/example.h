#ifndef _TVGEX_EXAMPLE_H_
#define _TVGEX_EXAMPLE_H_

#include <thorvg.h>
#include <imgui.h>
#include <nengine.h>

namespace tvgex::example
{

class Example
{
public:
	virtual const std::string& toString() = 0;
	virtual bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) = 0;
	virtual bool update(tvg::Canvas* canvas, double deltaTime)
	{
		return false;
	}
	virtual void drawUIWidgets(){}
	virtual void drawUIWindows(){}
};

}	 // namespace tvgex::example

namespace tvgex
{

inline bool verify(tvg::Result result, std::string failMsg = "")
{
	switch (result)
	{
		case tvg::Result::FailedAllocation:
		{
			NS_ERROR("FailedAllocation! {}", failMsg);
			return false;
		}
		case tvg::Result::InsufficientCondition:
		{
			NS_ERROR("InsufficientCondition! {}", failMsg);
			return false;
		}
		case tvg::Result::InvalidArguments:
		{
			NS_ERROR("InvalidArguments! {}", failMsg);
			return false;
		}
		case tvg::Result::MemoryCorruption:
		{
			NS_ERROR("MemoryCorruption! {}", failMsg);
			return false;
		}
		case tvg::Result::NonSupport:
		{
			NS_ERROR("NonSupport! {}", failMsg);
			return false;
		}
		case tvg::Result::Unknown:
		{
			NS_ERROR("Unknown! {}", failMsg);
			return false;
		}
		default:
			break;
	};
	return true;
}

inline double pingpong(double globalTime, double animationDurationMs, bool rewind = false)
{
	if (globalTime < 0.001)
		return 0.0f;
	auto forward = (static_cast<long long>(globalTime/animationDurationMs) % 2 == 0) ? true : false;
    auto remain = fmod(globalTime, animationDurationMs);
	auto progress = (remain / animationDurationMs);
	if (rewind)
		return forward ? progress : (1.0f - progress);
	return progress;
}
}	 // namespace tvgex

#endif