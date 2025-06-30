#ifndef _NS_GRAPHICS_CORE_SCENE_NSENTITY_H_
#define _NS_GRAPHICS_CORE_SCENE_NSENTITY_H_

#include "scene/nsScene.h"
#include "../common/common.h"

#include <vector>
#include <memory>

namespace ns
{

class UserEntity;
class Scene;

class Entity
{
public:

	virtual ~Entity() = default;

    template <class T>
    T &getComponent()
    {
        assert(hasComponent<T>());
		return r_scene_->registry_.get<T>(handle_);
    }

	template<typename T, typename... Args>
    T &addComponent(Args&&... args)
    {
        assert(!hasComponent<T>());
		return r_scene_->registry_.emplace<T>(handle_, std::forward<Args>(args)...);
    }

	template<typename T>
    bool hasComponent() 
    {
        return r_scene_->registry_.try_get<T>(handle_) != nullptr; 
    }

protected:
    friend class Scene;
    friend class UserEntity;
	Entity(Scene* scene);
	
    entt::entity handle_{ entt::null };
	Scene* r_scene_{nullptr};
};

}	 // namespace ns

#endif
