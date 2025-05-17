#ifndef _NS_GRAPHICS_CORE_COMMON_MAT_H
#define _NS_GRAPHICS_CORE_COMMON_MAT_H

#include "nsVector.h"

namespace ns
{

/**
 * col:
 * - v11, v21, v31, v41
 * - v12, v22, v32, v42
 * - v13, v23, v33, v43
 * - v14, v24, v34, v44
 * row:
 * - v11, v12, v13, v14
 * - v21, v22, v23, v24
 * - v31, v32, v33, v34
 * - v41, v42, v43, v44
 */
template <typename T>
struct Mat4x4
{
	using Col = Vector4<T>;
	Col value[4];

	Col& operator[](size_t row)
	{
		return value[row];
	}
	const Col& operator[](size_t row) const
	{
		return value[row];
	}
	Mat4x4()
	{
		value[0] = {1, 0, 0, 0};
		value[1] = {0, 1, 0, 0};
		value[2] = {0, 0, 1, 0};
		value[3] = {0, 0, 0, 1};
	}
};
template <typename T>
struct Mat3x3
{
	using Col = Vector3<T>;
	Col value[3];

	Col& operator[](size_t row)
	{
		return value[row];
	}
	const Col& operator[](size_t row) const
	{
		return value[row];
	}
	Mat3x3()
	{
		value[0] = {1, 0, 0};
		value[1] = {0, 1, 0};
		value[2] = {0, 0, 1};
	}
};

using Mat4 = Mat4x4<float>;
using Mat3 = Mat3x3<float>;

// 1x3 * 3x3 = 1x3
// 1x3, 3x1 is same type -> vector
template <typename T>
Vector3<T> operator*(const Vector3<T>& a, const Mat3x3<T>& b)
{
	Vector3<T> ret;

	// col
	ret[0] = a * b[0];
	ret[1] = a * b[1];
	ret[2] = a * b[2];

	// row
	// ret[0] = a[0] * b[0][0] + a[1] * b[1][0] + a[2] * b[2][0];
	// ret[1] = a[0] * b[0][1] + a[1] * b[1][1] + a[2] * b[2][1];
	// ret[2] = a[0] * b[0][2] + a[1] * b[1][2] + a[2] * b[2][2];

	return ret;
}

// 3x3 x 3x1 = 3x1
// 1x3, 3x1 is same type -> vector
template <typename T>
Vector3<T> operator*(const Mat3x3<T>& a, const Vector3<T>& b)
{
	Vector3<T> ret;

	// col
	ret[0] = b[0] * a[0][0] + b[1] * a[1][0] + b[2] * a[2][0];
	ret[1] = b[0] * a[0][1] + b[1] * a[1][1] + b[2] * a[2][1];
	ret[2] = b[0] * a[0][2] + b[1] * a[1][2] + b[2] * a[2][2];

	// row
	// ret[0] = a[0] * b
	// ret[1] = a[1] * b
	// ret[2] = a[2] * b

	return ret;
}

template <typename T>
Mat3x3<T> operator*(const Mat3x3<T>& a, const Mat3x3<T>& b)
{
	Mat3x3<T> ret;

	// col
	ret[0] = a * b[0];
	ret[1] = a * b[1];
	ret[2] = a * b[2];

	return ret;
}

// 1x4 * 4x4 = 1x4
template <typename T>
Vector4<T> operator*(const Vector4<T>& a, const Mat4x4<T>& b)
{
	Vector4<T> ret;

	ret[0] = a * b[0];
	ret[1] = a * b[1];
	ret[2] = a * b[2];
	ret[3] = a * b[3];

	// row
	// ret[0] = a[0] * b[0][0] + a[1] * b[1][0] + a[2] * b[2][0] + a[3] * b[3][0];
	// ret[1] = a[0] * b[0][1] + a[1] * b[1][1] + a[2] * b[2][1] + a[3] * b[3][1];
	// ret[2] = a[0] * b[0][2] + a[1] * b[1][2] + a[2] * b[2][2] + a[3] * b[3][2];
	// ret[3] = a[0] * b[0][3] + a[1] * b[1][3] + a[2] * b[2][3] + a[3] * b[3][3];
	return ret;
}

// 4x4 x 4x1 = 4x1
template <typename T>
Vector4<T> operator*(const Mat4x4<T>& a, const Vector4<T>& b)
{
	Vector4<T> ret;

	ret[0] = a[0][0] * b[0] + a[1][0] * b[1] + a[2][0] * b[2] + a[3][0] * b[3];
	ret[1] = a[0][1] * b[0] + a[1][1] * b[1] + a[2][1] * b[2] + a[3][1] * b[3];
	ret[2] = a[0][2] * b[0] + a[1][2] * b[1] + a[2][2] * b[2] + a[3][2] * b[3];
	ret[3] = a[0][3] * b[0] + a[1][3] * b[1] + a[2][3] * b[2] + a[3][3] * b[3];

	// row
	// ret[0] = a[0] * b;
	// ret[1] = a[1] * b;
	// ret[2] = a[2] * b;
	// ret[3] = a[3] * b;

	return ret;
}

template <typename T>
Mat4x4<T> operator*(const Mat4x4<T>& a, const Mat4x4<T>& b)
{
	Mat4x4<T> ret;

	// col
	ret[0] = a * b[0];
	ret[1] = a * b[1];
	ret[2] = a * b[2];
	ret[3] = a * b[3];

	// row
	// ret[0] = a[0] * b;
	// ret[1] = a[1] * b;
	// ret[2] = a[2] * b;
	// ret[3] = a[3] * b;

	return ret;
}

}	 // namespace ns

#endif