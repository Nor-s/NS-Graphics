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
	static std::unique_ptr<Entity> CreateEntity(Scene* scene, std::string_view name);

public:
	Scene();
	virtual ~Scene();
	virtual void init(const Resolution& res);
	virtual void resize(const Resolution& res);
	virtual void draw() {};
	uint64_t getSceneImage();
	Resolution getResolution();
	virtual InputController* getInputController();

	virtual void onUpdate();
	virtual void onRender();

protected:
	uint32_t getRenderId();

    friend class Entity;
    entt::registry registry_{};
	InputController* r_inputController_;
	UserEntity* user_ = nullptr;

private:
	std::unique_ptr<GlRenderer> glRenderer_;
	const CameraComponent* mainCamera_ = nullptr;
};

}	 // namespace ns

#endif