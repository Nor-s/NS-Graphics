#ifndef _NS_GRAPHICS_CORE_COMMON_RANDOM_H_
#define _NS_GRAPHICS_CORE_COMMON_RANDOM_H_

#include <random>

namespace ns {

class Random
{
	static std::random_device rd;
	static std::mt19937 mt19937;

public:
	static int RangeInt(int min, int max)
	{
		std::uniform_int_distribution dis(min, max);
		return dis(mt19937);
	}
	template<typename T>
	static T Range(double min, double max)
	{
		std::uniform_real_distribution dis(min, max);
		return static_cast<T>(dis(mt19937));
	}
};

} // namespace ns

#endif