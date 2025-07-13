#ifndef _NS_GRAPHICS_CORE_COMMON_NS_INTERPOLATION_H_
#define _NS_GRAPHICS_CORE_COMMON_NS_INTERPOLATION_H_

#include "nsTransform.h"
#include "nsMat.h"

namespace ns
{

class Interpolation
{
public:
    static ns::Vec3 Lerp(const ns::Vec3& start, const ns::Vec3& end, float t)
    {
        return start + (end - start) * t;
    }
};
}


#endif