#ifndef _NS_GRAPHICS_CORE_COMMON_SINGLEINSTANCE_H_
#define _NS_GRAPHICS_CORE_COMMON_SINGLEINSTANCE_H_

namespace ns
{

template <typename T>
class SingleInstance
{
protected:
	SingleInstance() = default;

public:
	SingleInstance(SingleInstance<T>&&) = delete;
	SingleInstance(const SingleInstance<T>&) = delete;

	SingleInstance<T>& operator=(const SingleInstance<T>&) = delete;
	SingleInstance<T>& operator=(SingleInstance<T>&&) = delete;

	~SingleInstance() = default;

	static T& Get()
	{
		static T s_instance;
		return s_instance;
	}
};

}	 // namespace ns

#endif