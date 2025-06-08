#ifndef _EX__ALGORITHM_REGION_H_
#define _EX__ALGORITHM_REGION_H_

#include <numeric>
#include <algorithm>
#include <set>
#include <vector>

struct Region
{
	size_t x1, y1;
	size_t x2, y2;
};

inline static Region scale(const Region& r, float s)
{
	float width = r.x2 - r.x1;
	float height = r.y2 - r.y1;
	width *= s;
	height *= s;
	return Region{
		.x1 = static_cast<size_t>(r.x1),
		.x2 = static_cast<size_t>(r.x1 + width),
		.y1 = static_cast<size_t>(r.y1),
		.y2 = static_cast<size_t>(r.y1 + height),
	};
}

inline static bool checkInner(const Region& small, const Region& big)
{
	return (big.x1 <= small.x1 && small.x2 <= big.x2 && big.y1 <= small.y1 && small.y2 <= big.y2);
}

inline static bool checkContain(size_t x, size_t y, const Region& big)
{
	return (big.x1 <= x && x <= big.x2) && (big.y1 <= y && y <= big.y2);
}

inline static bool checkClose(const Region& a, const Region& b)
{
	return !(a.x2 < b.x1 || a.x1 > b.x2 || a.y2 < b.y1 || a.y1 > b.y2);
}
inline static bool checkIntersect(const Region& a, const Region& b)
{
	return !(a.x2 <= b.x1 || a.x1 >= b.x2 || a.y2 <= b.y1 || a.y1 >= b.y2);
}

inline static bool canMerge(const Region& a, const Region& b)
{
	return checkInner(a, b) || checkInner(b, a);
}

inline static bool checkValid(const Region& a)
{
	return a.x1 < a.x2 && a.y1 < a.y2;
}

inline static Region getIntersect(const Region& a, const Region& b)
{
	Region ret;

	ret.x1 = std::max(a.x1, b.x1);
	ret.y1 = std::max(a.y1, b.y1);
	ret.x2 = std::min(a.x2, b.x2);
	ret.y2 = std::min(a.y2, b.y2);

	return ret;
}

inline static float area(const Region& a)
{
	if(a.x2 < a.x1 || a.y2 < a.y2)
		return 0.0;
	return (a.x2 - a.x1) * (a.y2 - a.y1);
}

class less_y1
{
public:
	bool operator()(const Region& lhs, const Region& rhs)
	{
		return lhs.y1 < rhs.y1;
	}
};

class less_x1
{
public:
	bool operator()(const Region& lhs, const Region& rhs)
	{
		return lhs.x1 < rhs.x1;
	}
};

class less_x1y1
{
public:
	bool operator()(const Region& lhs, const Region& rhs)
	{
		if (lhs.x1 == rhs.x1)
			return lhs.x1 < rhs.x1;
		return lhs.y1 < rhs.y1;
	}
};

class less_y2x1x2
{
public:
	bool operator()(const Region& lhs, const Region& rhs)
	{
		if(lhs.y2 != rhs.y2)
			return lhs.y2 < rhs.y2;

		if(lhs.x1 != rhs.x1)
			return lhs.x1 < rhs.x1;

		return lhs.x2 < rhs.x2;
	}
};
class less_x2y1y2
{
public:
	bool operator()(const Region& lhs, const Region& rhs)
	{
		if(lhs.x2 != rhs.x2)
			return lhs.x2 < rhs.x2;

		if(lhs.y1 < rhs.y1)
			return lhs.y1 < rhs.y1;
		return lhs.y2 < rhs.y2;
	}
};

class less_x1y1x2y2
{
public:
	bool operator()(const Region& lhs, const Region& rhs)
	{
		if (lhs.x1 != rhs.x1)
			return lhs.x1 < rhs.x1;

		if (lhs.y1 != rhs.y1)
			return lhs.y1 < rhs.y1;

		if (lhs.x2 != rhs.x2)
			return lhs.x2 > rhs.x2;

		return lhs.y2 > rhs.y2;
	}
};

struct RegionWrapper
{
	Region region;
	bool isInner = false;
};
class less_wrap_y1
{
public:
	bool operator()(const RegionWrapper& lhsw, const RegionWrapper& rhsw)
	{
		const auto& lhs = lhsw.region;
		const auto& rhs = rhsw.region;
		return lhs.y1 < rhs.y1;
	}
};

class less_wrap_x1
{
public:
	bool operator()(const RegionWrapper& lhsw, const RegionWrapper& rhsw)
	{
		const auto& lhs = lhsw.region;
		const auto& rhs = rhsw.region;
		return lhs.x1 < rhs.x1;
	}
};

class less_wrap_x1y1
{
public:
	bool operator()(const RegionWrapper& lhsw, const RegionWrapper& rhsw)
	{
		const auto& lhs = lhsw.region;
		const auto& rhs = rhsw.region;
		if (lhs.x1 == rhs.x1)
			return lhs.x1 < rhs.x1;
		return lhs.y1 < rhs.y1;
	}
};
class less_wrap_y2x1x2
{
public:
	bool operator()(const RegionWrapper& lhsw, const RegionWrapper& rhsw)
	{
		const auto& lhs = lhsw.region;
		const auto& rhs = rhsw.region;
		if(lhs.y2 != rhs.y2)
			return lhs.y2 < rhs.y2;

		if(lhs.x1 != rhs.x1)
			return lhs.x1 < rhs.x1;

		return lhs.x2 < rhs.x2;
	}
};
class less_wrap_x2y1y2
{
public:
	bool operator()(const RegionWrapper& lhsw, const RegionWrapper& rhsw)
	{
		const auto& lhs = lhsw.region;
		const auto& rhs = rhsw.region;
		if(lhs.x2 != rhs.x2)
			return lhs.x2 < rhs.x2;

		if(lhs.y1 < rhs.y1)
			return lhs.y1 < rhs.y1;
		return lhs.y2 < rhs.y2;
	}
};

class less_wrap_x1y1x2y2
{
public:
	bool operator()(const RegionWrapper& lhsw, const RegionWrapper& rhsw)
	{
		const auto& lhs = lhsw.region;
		const auto& rhs = rhsw.region;

		if (lhs.x1 != rhs.x1)
			return lhs.x1 < rhs.x1;

		if (lhs.y1 != rhs.y1)
			return lhs.y1 < rhs.y1;

		if (lhs.x2 != rhs.x2)
			return lhs.x2 > rhs.x2;

		return lhs.y2 > rhs.y2;
	}
};

using Regions = std::vector<Region>;
using RegionSet = std::set<Region, less_x1y1x2y2>;
using RegionWrappers = std::vector<RegionWrapper>;



#endif