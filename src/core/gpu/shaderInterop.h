#ifndef _NS_GRAPHICS_CORE_GPU_SHADER_INTEROP_H_
#define _NS_GRAPHICS_CORE_GPU_SHADER_INTEROP_H_

#include "../common/common.h"

#define INTEROP_VAR(type, var)  \
    type var{}; \
    static constexpr const char* var##_name = #var;

#define INTEROP_VAR_WITH_INIT(type, var, init)  \
    type var{init}; \
    static constexpr const char* var##_name = #var;

#define INTEROP_UBO_VAR(type, var)  \
    type var;



namespace ns
{

    /* alignas(16) */
    struct ShaderCameraInterop
    {
        INTEROP_VAR(ns::Mat4, view);
        INTEROP_VAR(ns::Mat4, proj);
        
        INTEROP_VAR(ns::Vec3, eyeWorldPosition);
        INTEROP_VAR(float,    nearZ);

        INTEROP_VAR(ns::Vec3, up);
        INTEROP_VAR(float,    farZ);

        INTEROP_VAR(ns::Vec3, atWorldPosition);
        INTEROP_VAR(float, fov);
    };

    struct BasicLightInterop
    {
        INTEROP_VAR_WITH_INIT(ns::Vec3, color, ns::Vec3(1.0f, 0.5f, 0.25f));
        INTEROP_VAR_WITH_INIT(ns::Vec3, lightColor, ns::Vec3(1.0f,1.0f,1.0f));
        INTEROP_VAR_WITH_INIT(ns::Vec3, lightPos, ns::Vec3(0.0f, 100.0f, 0.0f));
    };

    struct BasicLightInstancingInterop
    {
        INTEROP_VAR_WITH_INIT(ns::Vec3, color, ns::Vec3(1.0f, 0.5f, 0.25f));
        INTEROP_VAR_WITH_INIT(ns::Vec3, lightColor, ns::Vec3(1.0f,1.0f,1.0f));
        INTEROP_VAR_WITH_INIT(ns::Vec3, lightPos, ns::Vec3(0.0f, 100.0f, 0.0f));
        std::vector<ns::Vec4> instancingData_;
    };

    struct SolidColorInterop
    {
        INTEROP_VAR_WITH_INIT(ns::Vec3, color, ns::Vec3(1.0f,1.0f,1.0f));
    };

}

#endif