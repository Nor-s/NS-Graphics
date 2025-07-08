#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_

#include <memory>
#include "core/common/nsTransform.h"
#include "camera.h"
#include "core/gpu/geometry.h"
#include "callbackComponent.h"
#include "tags.h"

namespace ns
{

class GlGeometry;
struct NameComponent
{
	NameComponent(std::string_view name) : name(name)
	{
	}
	std::string name;
};

struct TransformComponent
{
	Transform transform;
};

struct GeometryComponent
{
	std::unique_ptr<Geometry> geometry;
};

struct CameraComponent
{
	Camera camera;
};

struct UpdateComponent
{
};

}	 // namespace ns

#endif