#ifndef _NS_GRAPHICS_CORE_COMMON_MAT_H
#define _NS_GRAPHICS_CORE_COMMON_MAT_H

#include "nsVector.h"

namespace ns
{

template <typename T>
struct Mat4x4
{
    T value[4][4];
};
template <typename T>
struct Mat3x3
{
    T value[3][3];
};

using Mat4 = Mat4x4<float>;
using Mat3 = Mat3x3<float>;

}

#endif