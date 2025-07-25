#ifndef _NS_CORE_COMMON_TIME_H_
#define _NS_CORE_COMMON_TIME_H_

#include <chrono>

namespace ns
{
class Timer
{
	using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

public:
	Timer()
	{
		reset();
	}
	~Timer()
	{
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
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		return elapsed.count()/1000.0;
	}
	double elapsed()
	{
		TimePoint end = std::chrono::system_clock::now();
		double ret = duration(before_, end);
		before_ = end;
		return ret;
	}
	void reset()
	{
		start_ = std::chrono::system_clock::now();
		before_ = start_;
	}

private:
	TimePoint start_;
	TimePoint before_;
};
}	 // namespace ns

#endif