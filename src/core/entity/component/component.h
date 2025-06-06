#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENT_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENT_H_

namespace ns
{

class Entity;

typedef int* TypeID;

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;
	virtual TypeID getType() const = 0;
	virtual void update() = 0;
	virtual void render() = 0;

protected:
	Entity* owner_;
};

template <class T>
class ComponentBase : public Component
{
public:
	static TypeID type;

public:
	ComponentBase()
	{
	}
	virtual ~ComponentBase()
	{
	}
	virtual void update() override
	{
	}
	virtual void render() override
	{
	}

	TypeID getType() const override final
	{
		return T::type;
	}
};

template <typename T>
TypeID ComponentBase<T>::type((TypeID) (&T::type));

}	 // namespace ns

#endif