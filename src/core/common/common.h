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



struct VertexLayout
{
    uint32_t index;
    uint32_t size;
    uint32_t stride;
    size_t   offset;
};

// vec4 size list
// stride = vec4 * count
struct InstancingLayout
{
    uint32_t startIndex{0};
    uint32_t count{0};
};

using Layouts = std::vector<VertexLayout>;
using InstancingLayouts = InstancingLayout;
using InstancingData = std::vector<ns::Vec4>;
using IndexData = std::vector<uint32_t>;
using VertexData = std::vector<float>;

struct GeometryInfo
{
	VertexData vertex;
	IndexData  index;
	InstancingData instancingVertex;
};

}	 // namespace ns

#endif