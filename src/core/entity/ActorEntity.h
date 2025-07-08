#ifndef _NS_GRAPHICS_CORE_ENTITY_NS_OBJECT_H_
#define _NS_GRAPHICS_CORE_ENTITY_NS_OBJECT_H_

#include "nsEntity.h"

#include <memory>

namespace ns
{
class Scene;

class ActorEntity
{
public:
    ActorEntity() = default;
    virtual ~ActorEntity() = default;
    void init(const Entity& entity);

    template <class T>
    T &getComponent()
    {
        return entity_.getComponent<T>();
    }

	template<typename T, typename... Args>
    T &addComponent(Args&&... args)
    {
		return entity_.addComponent<T>(std::forward<Args>(args)...);
    }

	template<typename T>
    bool hasComponent() 
    {
        return entity_.hasComponent<T>();
    }

protected:
    Entity entity_;
};

}	 // namespace ns

#endif