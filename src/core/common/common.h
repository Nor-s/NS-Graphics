#ifndef _NS_CORE_COMMON_H_
#define _NS_CORE_COMMON_H_

#include <string_view>
#include <memory>
#include <numeric>

#include "nsTransform.h"
#include "./logger.h"
#include "mathUtil.h"

namespace ns
{
struct Resolution
{
	uint32_t width = 0;
	uint32_t height = 0;
};
struct Rect
{
	uint32_t x = 0, y = 0, w = 0, h = 0;
};

enum class ColorFormat
{
	RGBA8,
	R32
};

enum class DepthFormat
{
	NONE,
	DEPTH24_STENCIL8
};

struct GeometryInfo
{
	std::vector<float> vertex;
	std::vector<uint32_t> index;
};

struct VertexLayout
{
    uint32_t index;
    uint32_t size;
    uint32_t stride;
    size_t   offset;
};

using Layouts = std::vector<VertexLayout>;

}	 // namespace ns

#endif