#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENT_NS_MATERIALS_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENT_NS_MATERIALS_H_

#include "core/gpu/shaderInterop.h"

#include <vector>

#define MATERIAL_NAME(a)  \
    static constexpr const char* name = #a


namespace ns
{
class Scene;
class Entity;

struct BasicLightMaterial
{
    MATERIAL_NAME(BasicLightMaterial);
    BasicLightInterop interop;
};

struct BasicLightInstancingMaterial
{
    MATERIAL_NAME(BasicLightInstancingMaterial);
    BasicLightInstancingInterop interop;

    Entity createInstance(Scene* scene);
    void updateInstance(Entity& entity);
};

struct SolidColorMaterial
{
    MATERIAL_NAME(SolidColorMaterial);
    SolidColorInterop interop;
};


}	 // namespace ns

#endif