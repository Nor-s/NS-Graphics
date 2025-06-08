// //g++ -o test main.cpp

#include "dirtyRegion.h"

#include <vector>
#include <iostream>
#include <random>

using namespace std;

DirtyRegionAlgorithm* dirtyRegionAlgorithm = new SimpleSplitAndMerge();

struct DirtyRegion
{
	void add(const Region& region)
	{
		input.push_back(region);
	}
	const vector<Region>& result()
	{
		return output;
	}
	void run()
	{
		printf("\n\n**** Run Algorithms! ***\n\n");
		output = dirtyRegionAlgorithm->run(input);
		input.clear();
	}
	vector<Region> input;
	vector<Region> output;
};

int main(int argc, char** argv)
{
	DirtyRegion region;
	constexpr const size_t INPUT_COUNT = 100;
	constexpr const size_t WIDTH = 1000;
	constexpr const size_t HEIGHT = 1000;
	constexpr const size_t MAX_SIZE = 200;
	constexpr const size_t MIN_SIZE = 100;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> x1Rand(1, WIDTH);
	std::uniform_int_distribution<> y1Rand(1, HEIGHT);
	std::uniform_int_distribution<> sizeRand(MIN_SIZE, MAX_SIZE);

	// input
	for (auto i = 0; i < INPUT_COUNT; ++i)
	{
		auto x1 = static_cast<size_t>(x1Rand(gen));
		auto y1 = static_cast<size_t>(y1Rand(gen));
		auto x2 = static_cast<size_t>(x1 + sizeRand(gen));
		auto y2 = static_cast<size_t>(y1 + sizeRand(gen));
		region.add({x1, y1, x2, y2});
		printf("input: %zu %zu %zu %zu\n", x1, y1, x2, y2);
	}
	region.run();
	// output
    printf("output size: %zu inputSize: %zu\n", region.result().size(), INPUT_COUNT);
	for (auto& r : region.result())
	{
		printf("output: %zu %zu %zu %zu\n", r.x1, r.y1, r.x2, r.y2);
	}
	return 0;
}