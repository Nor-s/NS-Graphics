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

	ret[0] = ret[0] * scale.x;
	ret[1] = ret[1] * scale.y;
	ret[2] = ret[2] * scale.z;

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

	rotation[0] = {c, 0, -s, 0};		// x-axis
	rotation[1] = {0, 1, 0, 0};		// y-axis
	rotation[2] = {s, 0, c, 0};	// z-axis
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
Mat4x4<T> rotate(const Mat4x4<T>& transform, const ns::Vec3& axis, float radian)
{
	// Rodrigues' Rotation
	Mat4x4<T> rotation;

	auto s = std::sin(radian);
	auto c = std::cos(radian);

	rotation[0] = {(1-c)*axis.x*axis.x + c, (1-c)*axis.x*axis.y + s*axis.z, (1-c)*axis.x*axis.z - s*axis.y, 0};		// x-axis
	rotation[1] = {(1-c)*axis.x*axis.y - s*axis.z, (1-c)*axis.y*axis.y + c, (1-c)*axis.y*axis.z + s*axis.x, 0};		// y-axis
	rotation[2] = {(1-c)*axis.x*axis.z + s*axis.y, (1-c)*axis.y*axis.z - s*axis.x, (1-c)*axis.z*axis.z + c, 0};		// z-axis
	rotation[3] = {0, 0, 0, 1};		// translate

	return transform * rotation;
}

template <typename T>
Mat4x4<T> rotateX(const Mat4x4<T>& transform, float radian)
{
	return transform * rotateX<T>(radian);
}

template <typename T>
Mat4x4<T> rotateY(const Mat4x4<T>& transform, float radian)
{
	return transform * rotateY<T>(radian);
}

template <typename T>
Mat4x4<T> rotateZ(const Mat4x4<T>& transform, float radian)
{
	return transform * rotateZ<T>(radian);
}


template <typename T>
Mat4x4<T> lookAtRH(const Vector3<T>& eye, const Vector3<T>& at, const Vector3<T>& up)
{
	// world space -> view space
	// 1. translate Axis (world space and camera space share the origin)
	// ret[3] = {-eye.x, -eye.y, -eye.z, 0.0};
	// 2. rotate Axis (basis change)
	// inverse(r) => transpose(r) (orthogonal matrix)

	// x,y,z: rotation basis axis
	auto z = normalize(eye - at);		 // z // n // forward
	auto x = normalize(cross(up, z));	 // x // right
	auto y = normalize(cross(z, x));	 // v // up

	Mat4x4<T> ret;

	ret[0] = {x.x, y.x, z.x, 0};
	ret[1] = {x.y, y.y, z.y, 0};
	ret[2] = {x.z, y.z, z.z, 0};
	ret[3] = {-(eye * x), -(eye * y), -(eye * z), 1.0};

	return ret;
}

template <typename T1, typename T2>
T2 convert3(T1 otherVector)
{
	T2 ret;
	ret[0] = otherVector[0];
	ret[1] = otherVector[1];
	ret[2] = otherVector[2];
	return ret;
}
template <typename T1, typename T2>
T2 convert4(T1 otherVector)
{
	T2 ret;
	ret[0] = otherVector[0];
	ret[1] = otherVector[1];
	ret[2] = otherVector[2];
	ret[3] = otherVector[3];
	return ret;
}

template <typename T1, typename T2>
T2 convert4x4(T1 other)
{
	T2 ret;
	ret[0][0] = other[0][0];
	ret[0][1] = other[0][1];
	ret[0][2] = other[0][2];
	ret[0][3] = other[0][3];

	ret[1][0] = other[1][0];
	ret[1][1] = other[1][1];
	ret[1][2] = other[1][2];
	ret[1][3] = other[1][3];

	ret[2][0] = other[2][0];
	ret[2][1] = other[2][1];
	ret[2][2] = other[2][2];
	ret[2][3] = other[2][3];

	ret[3][0] = other[3][0];
	ret[3][1] = other[3][1];
	ret[3][2] = other[3][2];
	ret[3][3] = other[3][3];

	return ret;
}

Mat4 orthoRH(float left, float right, float bottom, float top, float near, float far);
Mat4 perspectiveRH(float left, float right, float bottom, float top, float near, float far);
Mat4 perspectiveRH(float verticalFov, float aspect, float near, float far);

struct Transform
{
	ns::Vec3 position{0.0f, 0.0f, 0.0f};
	ns::Vec3 scaleXYZ{1.0f, 1.0f, 1.0f};
	ns::Vec3 radianXYZ{0.0f, 0.0f, 0.0f};
	Mat4 get()
	{
		auto transform = translate({}, position);
		transform = rotateZ(transform, radianXYZ.z);
		transform = scale(transform, scaleXYZ);
		return transform;
	}
};

}	 // namespace ns

#endif