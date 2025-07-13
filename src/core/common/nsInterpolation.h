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
    static ns::Transform Lerp(const ns::Transform& start, const ns::Transform& end, float t)
    {
        ns::Transform result;
        result.position = Lerp(start.position, end.position, t);
        result.radianXYZ = end.radianXYZ; // todo: implement rotation interpolation
        result.scaleXYZ = Lerp(start.scaleXYZ, end.scaleXYZ, t);
        return result;
    }
    // https://easings.net/ko#easeOutBack
    static float EaseOutBack(float t, float overshootFactor = 1.70158f)
    {
        t = t - 1.0f;
        return t*t*((overshootFactor + 1.0f)*t+overshootFactor) + 1.0f;
    }
};
}


#endif