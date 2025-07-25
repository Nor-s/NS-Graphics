#include "nsScene.h"
#include "../gpu/gpu.h"
#include "../input/inputController.h"
#include "../entity/nsEntity.h"
#include "../entity/userEntity.h"
#include "../entity/component/components.h"

namespace ns
{

Entity Scene::CreateEntity(Scene* scene, std::string_view name)
{
	Entity entity(scene);
	entity.addComponent<InitializeState>();
	entity.addComponent<ActivateState>();
	entity.addComponent<UpdateState>();
	entity.addComponent<TransformComponent>();
	entity.addComponent<NameComponent>(name.empty() ? "Entity" : name);

	return entity;
}

Entity Scene::createEntity(std::string_view name)
{
	return CreateEntity(this, name);
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
		user_->init(CreateEntity(this, "user"));
		inputController_ = std::make_unique<InputController>();
		user_->setupInputController(inputController_.get());
		if (inputController_->size() == 0)
		{
			inputController_.reset();
		}
		else
		{
			r_inputController_ = inputController_.get();
		}

		if (user_->hasComponent<CameraComponent>())
		{
			mainCamera_ = &(user_->getComponent<CameraComponent>());
			mainCamera_->camera.setRes(res);
		}
	}
}

void Scene::resize(const Resolution& res)
{
	glRenderer_->onResize(res);
	if(mainCamera_)
	{
		mainCamera_->camera.setRes(res);
	}
}

void Scene::onUpdate()
{
	// Adding/Removing components during iterations is safe
	// - https://github.com/skypjack/entt/issues/98
	// - https://github.com/skypjack/entt/issues/120

	// todo: destroy, deactivate callback

	// init callback
	registry_.view<InitializeState, BasicLightInstancingMaterial, GeometryComponent>().each(
		[&](const entt::entity& entity, auto& statetate, BasicLightInstancingMaterial& mat, GeometryComponent& geo)
		{
			geo.geometry->pushInstancingLayout(4, 4);
			geo.geometry->pushInstancingLayout(8, 1);
		});
	registry_.view<InitializeState, InitializeCallback>().each(
		[&](const entt::entity& entity, auto& statetate, auto& cb)
		{
			cb.callbackEvent->invoke();
		});
	registry_.clear<InitializeState>();

	registry_.view<ActivateState, ActivateCallback>().each(
		[&](const entt::entity& entity, auto& statetate, auto& cb)
		{
			cb.callbackEvent->invoke();
		});
	registry_.clear<ActivateState>();

	// updaate callback
	registry_.view<UpdateState, UpdateCallback>().each(
		[&](const entt::entity& entity, auto& state, auto& cb)
		{
			cb.callbackEvent->invoke();
		});
}

void Scene::onRender()
{
	glRenderer_->render(this);
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

const Camera* Scene::getMainCamera() const
{
	if(mainCamera_)
	{
		return &(mainCamera_->camera);
	}
	return nullptr;
}

}	 // namespace ns