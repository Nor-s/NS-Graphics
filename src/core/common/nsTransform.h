#ifndef _NS_GRAPHICS_CORE_COMMON_NS_TRANSFORM_H_
#define _NS_GRAPHICS_CORE_COMMON_NS_TRANSFORM_H_

#include "nsVector.h"
#include "nsMat.h"
#include <cmath>

namespace ns
{

// basis_x * translate_x + basis_y*translate_y +basis_z*translate_z + before translate
template <typename T>
Mat4x4<T> translate(const Mat4x4<T>& transform, const Vector3<T>& translate)
{
	Mat4x4<T> ret = transform;

	// col
	ret[3] = transform[0] * translate.x + transform[1] * translate.y + transform[2] * translate.z + transform[3];

	// row
	// ret[0][3] += transform[0][0] * translate[0] + transform[1][0] * translate[1] + transform[2][0] * translate[2];
	// ret[1][3] += transform[0][1] * translate[0] + transform[1][1] * translate[1] + transform[2][1] * translate[2];
	// ret[2][3] += transform[0][2] * translate[0] + transform[1][2] * translate[1] + transform[2][2] * translate[2];

	return ret;
}

// basis * scale
template <typename T>
Mat4x4<T> scale(const Mat4x4<T>& transform, Vec3 scale)
{
	Mat4x4<T> ret = transform;

	ret[0] = ret[0]*scale.x;
	ret[1] = ret[1]*scale.y;
	ret[2] = ret[2]*scale.z;

	return ret;
}

// basis * scale
template <typename T>
Mat4x4<T> scale(const Mat4x4<T>& transform, T scale)
{
	Mat4x4<T> ret = transform;

	ret[0] *= scale;
	ret[1] *= scale;
	ret[2] *= scale;

	return ret;
}

template <typename T>
Mat4x4<T> rotateX(float radian)
{
	Mat4x4<T> rotation;

	auto s = std::sin(radian);
	auto c = std::cos(radian);

	rotation[0] = {1, 0, 0, 0};		// x-axis
	rotation[1] = {0, c, s, 0};		// y-axis
	rotation[2] = {0, -s, c, 0};	// z-axis
	rotation[3] = {0, 0, 0, 1};		// translate

	return rotation;
}
template <typename T>
Mat4x4<T> rotateY(float radian)
{
	Mat4x4<T> rotation;

	auto s = std::sin(radian);
	auto c = std::cos(radian);

	rotation[0] = {c, 0, s, 0};		// x-axis
	rotation[1] = {0, 1, 0, 0};		// y-axis
	rotation[2] = {-s, 0, c, 0};	// z-axis
	rotation[3] = {0, 0, 0, 1};		// translate

	return rotation;
}
template <typename T>
Mat4x4<T> rotateZ(float radian)
{
	Mat4x4<T> rotation;

	auto s = std::sin(radian);
	auto c = std::cos(radian);

	rotation[0] = {c, s, 0, 0};		// x-axis
	rotation[1] = {-s, c, 0, 0};	// y-axis
	rotation[2] = {0, 0, 1, 0};		// z-axis
	rotation[3] = {0, 0, 0, 1};		// translate

	return rotation;
}

template <typename T>
Mat4x4<T> rotateX(const Mat4x4<T>& transform, float radian)
{
	return transform * rotateX<T>(radian) ;
}

template <typename T>
Mat4x4<T> rotateY(const Mat4x4<T>& transform, float radian)
{
	return  transform * rotateY<T>(radian) ;
}

template <typename T>
Mat4x4<T> rotateZ(const Mat4x4<T>& transform, float radian)
{
	return transform * rotateZ<T>(radian) ;
}

}	 // namespace ns

#endif