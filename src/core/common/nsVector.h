#ifndef _NS_GRAPHICS_CORE_COMMON_VECTOR3_H_
#define _NS_GRAPHICS_CORE_COMMON_VECTOR3_H_

namespace ns
{
template <typename T>
struct Vector2
{
	union
	{
		struct
		{
			T x, y;
		};
		struct
		{
			T r, g;
		};
		T value[2];
	};
};
template <typename T>
struct Vector3
{
	union
	{
		struct
		{
			T x, y, z;
		};
		struct
		{
			T r, g, b;
		};
		T value[3];
	};
};

template <typename T>
struct Vector4
{
	union
	{
		struct
		{
			T x, y, z, w;
		};
		struct
		{
			T r, g, b, a;
		};
		T value[4];
	};
};

using Vec2 = Vector2<float>;
using Vec3 = Vector3<float>;
using Vec4 = Vector4<float>;

}	 // namespace ns

#endif
