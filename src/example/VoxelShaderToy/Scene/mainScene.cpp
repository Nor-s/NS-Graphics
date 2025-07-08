#include "mainScene.h"
#include "Entity/user.h"
#include "Entity/box.h"

namespace vst
{

MainScene::MainScene()
{
	user_ = std::make_unique<User>();

	box_ = std::make_unique<BoxEntity>();
	{
		box_->init(CreateEntity(this, "box"));
		auto& geo = box_->addComponent<ns::GeometryComponent>();
		geo.geometry = ns::Geometry::CreateCube();
		box_->addComponent<ns::BasicLightMaterial>();
		box_->getComponent<ns::TransformComponent>().transform.scaleXYZ = {40.0f, 40.0f, 40.0f};
	}
}

}	 // namespace vst