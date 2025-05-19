#include "nsTransform.h"

namespace ns
{
Mat4 orthoRH(float left, float right, float bottom, float top, float near, float far)
{
	// 1. rotate right hand -> left hand
	// {1.0, 0.0, 0.0}
	// {0.0, 1.0, 0.0}
	// {0.0, 0.0, -1.0}

	// 2. scale Normalize -> [-1.0, 1.0]
	// {2/(l-r), 0.0, 0.0}
	// {0.0, 2/(t-b), 0.0}
	// {0.0, 0.0, 2/(f-n)}

	// 3. translate center View Volume
	// m[3] = {-(r+l)/2, -(t+b)/2, (f+n)/2}

	Mat4 ret;

	ret[0] = {2.0f / (right - left), 0.0f, 0.0f, 0.0f};
	ret[1] = {0.0f, 2.0f / (top - bottom), 0.0f, 0.0f};
	ret[2] = {0.0f, 0.0f, -2.0f / (far - near), 0.0f};
	ret[3] = {-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0};

	return ret;
}
}	 // namespace ns