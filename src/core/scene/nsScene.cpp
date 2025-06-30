#include "nsScene.h"
#include "../gpu/gpu.h"
#include "../input/inputController.h"
#include "../entity/nsEntity.h"
#include "../entity/userEntity.h"

namespace ns
{

std::unique_ptr<Entity> Scene::CreateEntity(Scene* scene, std::string_view name)
{
    std::unique_ptr<Entity> entity(new Entity(scene));
    entity->addComponent<TransformComponent>();
    entity->addComponent<TagComponent>(name.empty() ? "Entity" : name);
    return entity;
}

Scene::Scene()
{
}
Scene::~Scene() = default;

void Scene::init(const Resolution& res)
{
	glRenderer_.reset();
	glRenderer_ = std::make_unique<GlRenderer>();
	glRenderer_->onResize(res);

	if (user_)
	{
		// inputController_ = std::make_unique<InputController>();
		// user_->setupInputController(inputController_.get());
		// if (inputController_->size() == 0)
		// {
			// inputController_.reset();
		// }
	}
	else
	{
		// default user entity
		// user_ = std::make_unique<UserEntity>();
	}
	// mainCamera_ = &user_->getComponent<CameraComponent>();
}

void Scene::resize(const Resolution& res)
{
	glRenderer_->onResize(res);
}

void Scene::onUpdate()
{
}

void Scene::onRender()
{
	glRenderer_->onRender(this);
}

uint32_t Scene::getRenderId()
{
	return glRenderer_->getRenderTargetId();
}

uint64_t Scene::getSceneImage()
{
	return glRenderer_->getColorTexture();
}

Resolution Scene::getResolution()
{
	return glRenderer_->getResolution();
}

InputController* Scene::getInputController()
{
	return r_inputController_;
}

}	 // namespace ns