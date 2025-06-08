#ifndef _Algorithm_DirtyRegion_H_
#define _Algorithm_DirtyRegion_H_

#include "region.h"

class DirtyRegionAlgorithm
{
public:
	virtual Regions run(const Regions& input) = 0;
};

class SimpleSplit : public DirtyRegionAlgorithm
{
private:
	Regions buffer1;
	Regions buffer2;

public:
	// O(N*N)
	Regions run(const Regions& input)
	{
		Regions inputRegions = input;

		// O(NlogN)
		std::stable_sort(inputRegions.begin(), inputRegions.end(), less_x1y1());

		// O(N)
		buffer1.clear();
		buffer1.reserve(inputRegions.size());
		for (auto& region : inputRegions)
		{
			buffer1.emplace_back(region);
		}

		// O(NlogN)
		std::set<size_t> xAxis;
		std::set<size_t> yAxis;
		for (auto& region : inputRegions)
		{
			xAxis.insert(region.x1);
			xAxis.insert(region.x2);
			yAxis.insert(region.y1);
			yAxis.insert(region.y2);
		}

		// buffer1 size: N
		// find x: log(N)
		// average total xAxis iter: O(N)
		// worst total xAxis iter: O(N^2)
		// average(regionIter * findx + xAxisIter): O(N * logN + N)
		// worst: O(N^2)
		buffer2.clear();
		buffer2.reserve(buffer1.size());
		for (auto& region : buffer1)
		{
			Region remain = region;
			auto it = xAxis.lower_bound(remain.x1 + 1);
			for (; it != xAxis.end(); it++)
			{
				if (remain.x1 < *it && *it < remain.x2)
				{
					buffer2.push_back(Region{.x1 = remain.x1, .y1 = remain.y1, .x2 = *it, .y2 = remain.y2});
					remain.x1 = *it;
					continue;
				}
				break;
			}
			if (area(remain) != 0)
			{
				buffer2.push_back(remain);
			}
		}

		// buffer2 size: M
		// find y: log(N)
		// push result: log(N^2)
		// average total yAxis iter: O(N)
		// worst total yAxis iter: O(N^2)
		// average(regionIter * findy + yAxisIter): O(M * logN + N)
		// worst: O(N^2)
		std::set<Region, less_x1y1x2y2> result;
		for (auto& region : buffer2)
		{
			Region remain = region;
			auto it = yAxis.lower_bound(remain.y1 + 1);
			for (; it != yAxis.end(); it++)
			{
				if (remain.y1 < *it && *it < remain.y2)
				{
					result.insert(Region{.x1 = remain.x1, .y1 = remain.y1, .x2 = remain.x2, .y2 = *it});
					remain.y1 = *it;
					continue;
				}
				else
					break;
			}
			if (area(remain) != 0)
			{
				result.insert(remain);
			}
		}

		return Regions(result.begin(), result.end());
	}
};

/*
SimpleSplit's Optimize version . (TODO: FIX BUG)
*/
class SimpleSplit2 : public DirtyRegionAlgorithm
{
private:
	RegionWrappers buffer2;

public:
	Regions run(const Regions& input)
	{
		RegionWrappers inputRegions;

		for(auto& r: input)
		{
			inputRegions.push_back(RegionWrapper{.region=r, .isInner=false});
		}

		// split xAxis
		std::stable_sort(inputRegions.begin(), inputRegions.end(), less_wrap_x1y1());
		buffer2.clear();
		buffer2.reserve(inputRegions.size());
		bool isRefresh = false;
		int xIterSize = inputRegions.size();
		for (int i = 0; i < xIterSize; i++)
		{
			isRefresh = false;
			if(inputRegions[i].isInner)
			{
				continue;
			}
			Region remain = inputRegions[i].region;
			RegionWrapper rhs = inputRegions[i];
			rhs.region.x1 += 1;
			auto it = lower_bound(inputRegions.begin() + i, inputRegions.end(), rhs, less_wrap_x1y1());
			for (; it != inputRegions.end(); it++)
			{
				auto rhsx1 = it->region.x1;
				auto rhsx2 = it->region.x2;
				Region other = it->region;

				if (it->isInner || checkInner(other, remain))
				{
					it->isInner = true;
					continue;
				}
				if(checkIntersect(other, remain) == false) continue;

				bool bIsContinue = false;
				if (remain.x1 < rhsx1 && rhsx1 < remain.x2)
				{
					auto cacheX2 = remain.x2;
					remain.x2 = rhsx1;
					buffer2.push_back(RegionWrapper{.region=remain, .isInner=false});
					remain.x2 = cacheX2;
					remain.x1 = rhsx1;
					bIsContinue = true;
				}
				if(rhsx1 < remain.x2 && remain.x2 < rhsx2)
				{
					auto splitTarget = it->region;
					bool splitIsInner = it->isInner;
					it->isInner = true;
					inputRegions.push_back(RegionWrapper{.region=remain, .isInner=false});
					auto cacheX2 = splitTarget.x2;
					splitTarget.x2 = remain.x2;
					inputRegions.push_back(RegionWrapper{.region=splitTarget, .isInner=splitIsInner});
					splitTarget.x1 = remain.x2;
					splitTarget.x2 = cacheX2;
					inputRegions.push_back(RegionWrapper{.region=splitTarget, .isInner=splitIsInner});
					std::stable_sort(inputRegions.begin() + i + 1, inputRegions.end(), less_wrap_x1y1());
					isRefresh = true;
					xIterSize += 3;
					break;
				}

				if (remain.x1 < rhsx2 && rhsx2 < remain.x2)
				{
					auto cacheX2 = remain.x2;
					remain.x2 = rhsx2;
					inputRegions.push_back(RegionWrapper{.region=remain, .isInner=false});
					remain.x2 = cacheX2;
					remain.x1 = rhsx2;
					inputRegions.push_back(RegionWrapper{.region=remain, .isInner=false});
					std::stable_sort(inputRegions.begin() + i + 1, inputRegions.end(), less_wrap_x1y1());
					isRefresh = true;
					xIterSize += 2;
					break;
				}

				if (bIsContinue)
				{
					continue;
				}

				break;
			}
			if(isRefresh)
			{
				continue;
			}
			if (area(remain) != 0)
			{
				buffer2.push_back(RegionWrapper{.region=remain, .isInner=false});
			}
		}

		// split yAxis
		std::stable_sort(buffer2.begin(), buffer2.end(), less_wrap_y1());
		std::set<RegionWrapper, less_wrap_x1y1x2y2> resultSet;
		int yIterSize = buffer2.size();
		for (int i = 0; i < yIterSize; i++)
		{
			isRefresh = false;
			if(buffer2[i].isInner)
			{
				continue;
			}
			Region remain = buffer2[i].region;
			RegionWrapper rhs = buffer2[i];
			rhs.region.y1 += 1;
			auto it = lower_bound(buffer2.begin() + i, buffer2.end(), rhs, less_wrap_y1());
			for (; it != buffer2.end(); it++)
			{
				auto rhsy1 = it->region.y1;
				auto rhsy2 = it->region.y2;
				Region other = it->region;

				if (it->isInner || checkInner(other, remain))
				{
					it->isInner = true;
					continue;
				}
				if(checkIntersect(other, remain) == false) continue;

				bool bIsContinue = false;
				if (remain.y1 < rhsy1 && rhsy1 < remain.y2)
				{
					auto cachey2 = remain.y2;
					remain.y2 = rhsy1;
					resultSet.insert(RegionWrapper{.region=remain, .isInner=false});
					remain.y2 = cachey2;
					remain.y1 = rhsy1;
					bIsContinue = true;
				}
				if(rhsy1 < remain.y2 && remain.y2 < rhsy2)
				{
					auto splitTarget = it->region;
					it->isInner = true;
					buffer2.push_back(RegionWrapper{.region=remain, .isInner=false});
					auto cachey2 = splitTarget.y2;
					splitTarget.y2 = remain.y2;
					buffer2.push_back(RegionWrapper{.region=splitTarget, .isInner=false});
					splitTarget.y1 = remain.y2;
					splitTarget.y2 = cachey2;
					buffer2.push_back(RegionWrapper{.region=splitTarget, .isInner=false});
					std::stable_sort(buffer2.begin() + i + 1, buffer2.end(), less_wrap_y1());
					isRefresh = true;
					yIterSize += 3;
					break;
				}

				if (remain.y1 < rhsy2 && rhsy2 < remain.y2)
				{
					auto cachey2 = remain.y2;
					remain.y2 = rhsy2;
					buffer2.push_back(RegionWrapper{.region=remain, .isInner=false});
					remain.y2 = cachey2;
					remain.y1 = rhsy2;
					buffer2.push_back(RegionWrapper{.region=remain, .isInner=false});
					std::stable_sort(buffer2.begin() + i + 1, buffer2.end(), less_wrap_y1());
					isRefresh = true;
					yIterSize += 2;
					break;
				}

				if (bIsContinue)
				{
					continue;
				}

				break;
			}
			if(isRefresh)
			{
				continue;
			}
			if (area(remain) != 0)
			{
				resultSet.insert(RegionWrapper{.region=remain, .isInner=false});
			}
		}

		Regions result;
		result.reserve(resultSet.size());
		for(auto& r: resultSet)
		{
			if(r.isInner)
				continue;
			result.push_back(r.region);
		}
		return result;
	}
};


class SimpleSplitAndMerge : public DirtyRegionAlgorithm
{
protected:
	DirtyRegionAlgorithm* other_ = nullptr;
	SimpleSplit simpleSplit_;

	using LeftSet = std::set<Region, less_x2y1y2>;
	using UpSet = std::set<Region, less_y2x1x2>;

public:
	// set find:  O(logN)
	// set erase: O(logN)
	bool leftMerge(RegionSet& total, LeftSet& left, UpSet& up, Region& region)
	{
		auto it = left.find(Region{.x2 = region.x1, .y1 = region.y1, .y2 = region.y2});
		if (it == left.end())
		{
			return false;
		}

		region.x1 = (*it).x1;
		total.erase(*it);
		up.erase(*it);
		left.erase(it);
		return true;
	}
	// set find:  O(logN)
	// set erase: O(logN)
	bool upMerge(RegionSet& total, LeftSet& left, UpSet& up, Region& region)
	{
		auto it = up.find(Region{.y2 = region.y1, .x1 = region.x1, .x2 = region.x2});
		if (it == up.end())
		{
			return false;
		}

		region.y1 = (*it).y1;
		total.erase(*it);
		left.erase(*it);
		up.erase(it);
		return true;
	}
	Regions run(const Regions& input)
	{
		if(other_ == nullptr)
		{
			other_ = &simpleSplit_;
		}
		// O(N^2)
		// M = N^2
		Regions regions = other_->run(input);
		if (regions.empty())
			return regions;

		LeftSet left;
		UpSet up;
		std::set<Region, less_x1y1x2y2> resultSet;

		// region iter: O(M)
		// left merge: O(logM)
		// result set insert: O(logM)
		// left set insert: O(logM)
		// total: O(M * logM)
		// good: O(N * logN)
		// worst: O(N^2 * logN)
		Region currentRegion = regions[0];
		for (int i = 1; i < regions.size(); ++i)
		{
			auto region = regions[i];

			leftMerge(resultSet, left, up, currentRegion);
			leftMerge(resultSet, left, up, currentRegion);

			// merge down
			if (currentRegion.x1 == region.x1 && currentRegion.x2 == region.x2 && currentRegion.y2 == region.y1)
			{
				currentRegion.y2 = region.y2;
			}
			else
			{
				left.insert(currentRegion);
				resultSet.insert(currentRegion);
				currentRegion = region;
			}
		}

		// merge last region
		leftMerge(resultSet, left, up, currentRegion);
		upMerge(resultSet, left, up, currentRegion);
		resultSet.insert(currentRegion);

		return Regions(resultSet.begin(), resultSet.end());
	}
};


/*
SimpleSplit's Optimize version . (TODO: FIX BUG)
 */
class SimpleSplit2AndMerge : public SimpleSplitAndMerge
{
private:
	SimpleSplit2 split2_;
public:
	Regions run(const Regions& input)
	{
		other_ = &split2_;
		return SimpleSplitAndMerge::run(input);
	}
};


class SimpleSplit2_X : public DirtyRegionAlgorithm
{
private:
	RegionWrappers buffer2;

public:
	Regions run(const Regions& input)
	{
		RegionWrappers inputRegions;

		for(auto& r: input)
		{
			inputRegions.push_back(RegionWrapper{.region=r, .isInner=false});
		}

		// split xAxis
		std::stable_sort(inputRegions.begin(), inputRegions.end(), less_wrap_x1());
		buffer2.clear();
		buffer2.reserve(inputRegions.size());
		bool isRefresh = false;
		int xIterSize = inputRegions.size();
		for (int i = 0; i < xIterSize; i++)
		{
			isRefresh = false;
			if(inputRegions[i].isInner)
			{
				continue;
			}
			Region remain = inputRegions[i].region;
			RegionWrapper rhs = inputRegions[i];
			rhs.region.x1 += 1;
			auto it = lower_bound(inputRegions.begin() + i, inputRegions.end(), rhs, less_wrap_x1());
			for (; it != inputRegions.end(); it++)
			{
				auto rhsx1 = it->region.x1;
				auto rhsx2 = it->region.x2;
				Region other = it->region;

				if (it->isInner || checkInner(other, remain))
				{
					it->isInner = true;
					continue;
				}
				if(checkClose(other, remain) == false) continue;

				bool bIsContinue = false;
				if (remain.x1 < rhsx1 && rhsx1 < remain.x2)
				{
					auto cacheX2 = remain.x2;
					remain.x2 = rhsx1;
					buffer2.push_back(RegionWrapper{.region=remain, .isInner=false});
					remain.x2 = cacheX2;
					remain.x1 = rhsx1;
					bIsContinue = true;
				}
				if(rhsx1 < remain.x2 && remain.x2 < rhsx2)
				{
					auto splitTarget = it->region;
					bool splitIsInner = it->isInner;
					it->isInner = true;
					inputRegions.push_back(RegionWrapper{.region=remain, .isInner=false});
					auto cacheX2 = splitTarget.x2;
					splitTarget.x2 = remain.x2;
					inputRegions.push_back(RegionWrapper{.region=splitTarget, .isInner=splitIsInner});
					splitTarget.x1 = remain.x2;
					splitTarget.x2 = cacheX2;
					inputRegions.push_back(RegionWrapper{.region=splitTarget, .isInner=splitIsInner});
					std::stable_sort(inputRegions.begin() + i + 1, inputRegions.end(), less_wrap_x1());
					isRefresh = true;
					xIterSize += 3;
					break;
				}

				if (remain.x1 < rhsx2 && rhsx2 < remain.x2)
				{
					auto cacheX2 = remain.x2;
					remain.x2 = rhsx2;
					inputRegions.push_back(RegionWrapper{.region=remain, .isInner=false});
					remain.x2 = cacheX2;
					remain.x1 = rhsx2;
					inputRegions.push_back(RegionWrapper{.region=remain, .isInner=false});
					std::stable_sort(inputRegions.begin() + i + 1, inputRegions.end(), less_wrap_x1());
					isRefresh = true;
					xIterSize += 2;
					break;
				}

				if (bIsContinue)
				{
					continue;
				}

				break;
			}
			if(isRefresh)
			{
				continue;
			}
			if (area(remain) != 0)
			{
				buffer2.push_back(RegionWrapper{.region=remain, .isInner=false});
			}
		}

		Regions ret;
		ret.reserve(buffer2.size());
		for(auto& b: buffer2)
		{
			if(b.isInner == false)
			{
				ret.push_back(b.region);
			}
		}
		return ret;
	}
};


#endif