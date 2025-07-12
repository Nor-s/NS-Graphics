#include "nsMaterial.h"
#include "components.h"
#include "scene/nsScene.h"
#include "entity/nsEntity.h"

#include <string>
#include <algorithm>
#include <numeric>

namespace ns
{

Entity BasicLightInstancingMaterial::createInstance(Scene* scene)
{
	assert(scene);

	interop.bIsDirty = true;

	int idx = interop.transform.size();
	auto name = std::to_string(idx);

	Entity entity = scene->createEntity(name);
	auto& instancingComponent = entity.addComponent<InstancingComponent<BasicLightInstancingMaterial>>(idx, *this);
	auto& colorComponent = entity.addComponent<ColorComponent>();
	interop.color.push_back({0.0f, 0.0f, 0.0f, 1.0f});
	interop.transform.push_back(entity.getComponent<TransformComponent>().transform.get());

	return entity;
}

void BasicLightInstancingMaterial::updateInstance(Entity& entity)
{
	if (!entity.hasComponent<InstancingComponent<BasicLightInstancingMaterial>>())
	{
		return;
	}

	auto instancing = entity.getComponent<InstancingComponent<BasicLightInstancingMaterial>>();
	if (&instancing.material == this)
	{
		interop.bIsDirty = true;
		int idx = instancing.instancingIdx;
		interop.transform[idx] = entity.getComponent<TransformComponent>().transform.get();
		interop.color[idx] = entity.getComponent<ColorComponent>().color;
	}
}

}	 // namespace ns