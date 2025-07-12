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
		geo.geometry = ns::Geometry::CreateCubeWithNormal();
		auto& instancing = box_->addComponent<ns::BasicLightInstancingMaterial>();
		box_->getComponent<ns::TransformComponent>().transform.scaleXYZ = {40.0f, 40.0f, 40.0f};

		instancing.interop.lightPos = {1500.0f, 1500.0f, 1600.0f};
		block_.resize(length_, std::vector<std::vector<ns::Entity>>(length_, std::vector<ns::Entity>(length_)));

		for(int i = 0; i < length_; ++i)
		{
			for(int j = 0; j < length_; ++j)
			{
				for(int k = 0; k < length_; ++k)
				{
					block_[i][j][k] = instancing.createInstance(this);
					auto& instance = block_[i][j][k];
					instance.getComponent<ns::TransformComponent>().transform.position = {
						i * 11.0f,
						j * 11.0f,
						k * 11.0f
					};
					instance.getComponent<ns::TransformComponent>().transform.scaleXYZ = {
						10.0f,
						10.0f,
						10.0f
					};
					instance.getComponent<ns::ColorComponent>().color = {
						(float)i/length_ ,
						(float)j/length_,
						(float)k/length_,
						1.0f
					};
					instancing.updateInstance(instance);
				}
			}
		}
	}
}

}	 // namespace vst