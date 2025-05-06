#ifndef _NS_CORE_COMMON_TIME_H_
#define _NS_CORE_COMMON_TIME_H_

#include <chrono>
#include <sglib.h>

namespace ns
{
class Timer
{
	using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

public:
	Timer()
	{
		start_ = std::chrono::system_clock::now();
		before_ = start_;
	}
	~Timer()
	{
		double ms = duration();
		SG_LOG_INFO("duration: {}ms", ms);
	}
	double duration()
	{
		return duration(start_);
	}
	double duration(TimePoint& start)
	{
		TimePoint end = std::chrono::system_clock::now();
		return duration(start, end);
	}
	double duration(const TimePoint& start, const TimePoint& end)
	{
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		return static_cast<double>(elapsed.count());
	}
	double elapsed()
	{
		TimePoint end = std::chrono::system_clock::now();
		double ret = duration(before_, end);
		before_ = end;
		return ret;
	}

private:
	TimePoint start_;
	TimePoint before_;
};
}	 // namespace ns

#endif