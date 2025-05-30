#ifndef _NS_GRAPHICS_CORE_COMMON_MATH_UTIL_H_
#define _NS_GRAPHICS_CORE_COMMON_MATH_UTIL_H_

#include <cmath>

namespace ns::math
{
    inline static float ToRadian(float angle)
    {
        return angle*(M_PI/180.0f);
    }
}

#endif