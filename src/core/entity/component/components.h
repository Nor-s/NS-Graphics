#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENTS_H_

#include <memory>
#include "core/common/nsTransform.h"
#include "camera.h"

namespace ns
{

class GlGeometry;

struct TagComponent
{
	TagComponent(std::string_view name) : name(name)
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
	std::shared_ptr<GlGeometry> geometry = nullptr;
};

struct CameraComponent
{
	Camera camera;
};

}	 // namespace ns

#endif