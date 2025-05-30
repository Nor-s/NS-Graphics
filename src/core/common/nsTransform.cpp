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

Mat4 perspectiveRH(float left, float right, float bottom, float top, float near, float far)
{
	// 1. x and y are projected onto the near plane
	//		X_proj = (near*X_eye)/(-Z_eye)
	// 		X_ndc = 2/width * X_proj + B
	// 		1 = 2/width * right + B
	// 		...
	// 		X_ndc = X_clip/(-Z_eye)
	//		X_clip = X_ndc/(-Z_eye)

	// 2. Z_ndc = Z_clip/W_clip
	//		Z_clip = A*Z_eye + B*W_eye (Z does not depend on X or Y)
	//		W_clip = -Z_eye
	//		Z_ndc = (A*Z_eye + B) / (-Z_eye)     (eye space, W_eye = 1)
	//			near: (-A*near + B)/ near = -1
	//				-A*near + B = - near
	//			far : (-A*far  + B)/ far  =  1
	//				-A*far + B = far
	// ...

	Mat4 ret;

	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	ret[0] = {2.0f * near / width, 0.0f, 0.0f, 0.0f};
	ret[1] = {0.0f, 2.0f * near / height, 0.0f, 0.0f};
	ret[2] = {(right + left) / width, (top + bottom) / height, -(far + near) / depth,
			  -1.0f};	 // -1.0f = for divided by -Zeye
	ret[3] = {0.0f, 0.0f, -2.0f * far * near / depth, 0.0f};

	return ret;
}

Mat4 perspectiveRH(float verticalFov, float aspect, float near, float far)
{
	// top/near = tan(fov/2)
	// top = tan(fov/2) * near
	// top : right = height : width
	// aspect = height/width
	// right = top / aspect

	float top = std::tan(verticalFov * 0.5f) * near;
	float right = top / aspect;

	Mat4 ret;

	// view volume is symmetric
	ret[0] = {near / right, 0.0f, 0.0f, 0.0f};
	ret[1] = {0.0f, near / top, 0.0f, 0.0f};
	ret[2] = {0.0f, 0.0f, -(far + near) / (far - near), -1.0f};
	ret[3] = {0.0f, 0.0f, -2.0f * far * near / (far - near), 0.0f};

	return ret;
}

}	 // namespace ns