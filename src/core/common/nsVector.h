#ifndef _NS_GRAPHICS_CORE_COMMON_VECTOR3_H_
#define _NS_GRAPHICS_CORE_COMMON_VECTOR3_H_

namespace ns
{
template <typename T>
struct Vector2
{
	using element_type = T;
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
		T value[2]={0,};
	};
	T& operator[](size_t col)
	{
		return value[col];
	}
	const T& operator[](size_t col) const
	{
		return value[col];
	}
};

template <typename T>
struct Vector3
{
	using element_type = T;
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
		T value[3]={0,};
	};
	Vector3()
	{
		memset(value, 0, sizeof value);
	}
	Vector3(T x, T y, T z)
	{
		value[0] = x;
		value[1] = y;
		value[2] = z;
	}
	T& operator[](size_t col)
	{
		return value[col];
	}
	const T& operator[](size_t col) const
	{
		return value[col];
	}
};

template <typename T>
struct Vector4
{
	using element_type = T;
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
		T value[4]={0,};
	};
	T& operator[](size_t col)
	{
		return value[col];
	}
	const T& operator[](size_t col) const
	{
		return value[col];
	}
	Vector4()
	{
		memset(value, 0, sizeof value);
	}
	Vector4(T x, T y, T z, T a)
	{
		value[0] = x;
		value[1] = y;
		value[2] = z;
		value[3] = a;
	}
};

using Vec2 = Vector2<float>;
using Vec3 = Vector3<float>;
using Vec4 = Vector4<float>;

// dot product
template <typename T>
T operator*(const Vector3<T>& a, const Vector3<T>& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b)
{
	return Vector3<T>{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename T>
Vector3<T> operator*(const Vector3<T>& a, T b)
{
	return Vector3<T>{a.x * b, a.y * b, a.z * b};
}

template <typename T>
Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b)
{
	return Vector3<T>{a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T>
Vector3<T> operator/(const Vector3<T>& a, T b)
{
	return Vector3<T>{a.x / b, a.y / b, a.z / b};
}

// dot product
template <typename T>
T operator*(const Vector4<T>& a, const Vector4<T>& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T>
Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b)
{
	return Vector4<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

template <typename T>
Vector4<T> operator*(const Vector4<T>& a, T b)
{
	return Vector4<T>{a.x * b, a.y * b, a.z * b, a.w * b};
}

template <typename T>
Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b)
{
	return Vector4<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

template <typename T>
Vector4<T> operator/(const Vector4<T>& a, T b)
{
	return Vector4<T>{a.x / b, a.y / b, a.z / b, a.w / b};
}

template <typename T>
auto length2(const T& a) -> decltype(a * a)
{
	return a * a;
}

template <typename T>
auto length(const T& a) -> decltype(sqrt(a * a))
{
	return sqrt(length2(a));
}

template <typename T>
const T normalize(const T& a)
{
	return a / length(a);
}

}	 // namespace ns

#endif
