#ifndef _NS_GRAPHICS_CORE_SCENE_NSENTITY_H_
#define _NS_GRAPHICS_CORE_SCENE_NSENTITY_H_

#include "../common/common.h"
#include "scene/nsScene.h"

#include <vector>
#include <memory>

#include <entt/entt.hpp>

namespace ns
{

class Entity
{
public:
	Entity() = default;
	Entity(Scene* scene);
	virtual ~Entity() = default;

	template <class T>
	T& getComponent()
	{
		assert(hasComponent<T>());
		return r_scene_->registry_.get<T>(handle_);
	}

	template <typename T, typename... Args>
	T& addComponent(Args&&... args)
	{
		assert(!hasComponent<T>());
		return r_scene_->registry_.emplace<T>(handle_, std::forward<Args>(args)...);
	}

	template <typename T>
	bool hasComponent()
	{
		assert(handle_ != entt::null);
		return r_scene_->registry_.try_get<T>(handle_) != nullptr;
	}

private:
	entt::entity handle_{entt::null};
	Scene* r_scene_{nullptr};
};

}	 // namespace ns

#endif
