#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENT_NS_MATERIALS_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENT_NS_MATERIALS_H_

#include "core/gpu/shaderInterop.h"

#define MATERIA_NAME(a)  \
    static constexpr const char* name = #a

namespace ns
{

struct BasicLightMaterial
{
    MATERIA_NAME(BasicLightMaterial);
    BasicLightInterop interop;
};

struct SolidColorMaterial
{
    MATERIA_NAME(SolidColorMaterial);
    SolidColorInterop interop;
};


}	 // namespace ns

#endif