#ifndef _NS_GRAPHICS_CORE_SCENE_SCEHE_H_
#define _NS_GRAPHICS_CORE_SCENE_SCEHE_H_

#include "entity/component/components.h"
#include "platform/platformEvent.h"

#include <vector>
#include <entt/entt.hpp>

namespace ns
{
class UserEntity;
class Entity;
class InputController;
class GlRenderer;

class Scene
{
public:
	static Entity CreateEntity(Scene* scene, std::string_view name);

public:
	Scene();
	virtual ~Scene();
	virtual void init(const Resolution& res);
	virtual void resize(const Resolution& res);
	virtual void draw() {};

	Entity createEntity(std::string_view name);

	uint64_t getSceneImage();
	Resolution getResolution();
	virtual InputController* getInputController();
	entt::registry& getRegistry()
	{
		return registry_;
	}
	const Camera* getMainCamera() const;
	

	virtual void onUpdate();
	virtual void onRender();

protected:
	uint32_t getRenderId();

	friend class Entity;
	entt::registry registry_{};
	InputController* r_inputController_;
	std::unique_ptr<UserEntity> user_;

private:
	std::unique_ptr<InputController> inputController_;
	std::unique_ptr<GlRenderer> glRenderer_;
	CameraComponent* mainCamera_ = nullptr;
};

}	 // namespace ns

#endif