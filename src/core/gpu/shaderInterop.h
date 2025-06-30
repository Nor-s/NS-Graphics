#ifndef _NS_GRAPHICS_CORE_GPU_SHADER_INTEROP_H_
#define _NS_GRAPHICS_CORE_GPU_SHADER_INTEROP_H_

#include "../common/common.h"

#define INTEROP_VAR(type, var)  \
    type var; \
    static constexpr const char* var##_name = #var;

#define INTEROP_UBO_VAR(type, var)  \
    type var;



namespace ns
{
    struct alignas(16) ShaderCameraInterop
    {
        INTEROP_VAR(ns::Mat4, view);
        INTEROP_VAR(ns::Mat4, proj);
        
        INTEROP_VAR(ns::Vec3, worldPosition);
        INTEROP_VAR(float,    nearZ);

        INTEROP_VAR(ns::Vec3, up);
        INTEROP_VAR(float,    farZ);

        INTEROP_VAR(ns::Vec3, atWorldPosition);
        INTEROP_VAR(float, fov);
    };
}

#endif