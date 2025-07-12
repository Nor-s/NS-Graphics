#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_

#include <memory>
#include "core/common/nsTransform.h"
#include "camera.h"
#include "core/gpu/geometry.h"
#include "callbackComponent.h"
#include "tags.h"
#include "nsMaterial.h"

namespace ns
{

class GlGeometry;

struct NameComponent
{
	NameComponent(std::string_view name) : name(name)
	{
	}
	std::string name{};
};

struct TransformComponent
{
	Transform transform{};
};
struct ColorComponent
{
	ns::Vec4 color;
};

struct GeometryComponent
{
	std::unique_ptr<Geometry> geometry{};
};

template <typename T>
struct InstancingComponent
{
	InstancingComponent(int instancingIdx, T& mat) : instancingIdx(instancingIdx), material(mat)
	{
	}
	int instancingIdx;
	T& material;
};

struct CameraComponent
{
	Camera camera{};
};

struct UpdateComponent
{
};

}	 // namespace ns

#endif