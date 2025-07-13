#include "mainScene.h"
#include "Entity/user.h"
#include "Entity/box.h"

#include "Entity/luaComponent.h"

std::array<ns::Vec3, 16> palette = {
    ns::Vec3{0.882f, 0.914f, 0.957f},  // 1
    ns::Vec3{0.427f, 0.455f, 0.573f},  // 2
    ns::Vec3{0.067f, 0.082f, 0.090f},  // 3
    ns::Vec3{0.918f, 0.675f, 0.655f},  // 4
    ns::Vec3{0.800f, 0.443f, 0.596f},  // 5
    ns::Vec3{0.212f, 0.090f, 0.263f},  // 6
    ns::Vec3{0.863f, 0.302f, 0.388f},  // 7
    ns::Vec3{0.906f, 0.545f, 0.388f},  // 8
    ns::Vec3{0.969f, 0.796f, 0.478f},  // 9
    ns::Vec3{0.000f, 0.000f, 0.000f},  // 10
    ns::Vec3{0.306f, 0.608f, 0.376f},  // 11
    ns::Vec3{0.200f, 0.180f, 0.329f},  // 12
    ns::Vec3{0.318f, 0.325f, 0.643f},  // 13
    ns::Vec3{0.176f, 0.216f, 0.302f},  // 14
    ns::Vec3{0.592f, 0.345f, 0.329f},  // 15
    ns::Vec3{0.290f, 0.157f, 0.212f}   // 16
};

namespace vst
{

MainScene::MainScene()
{
	user_ = std::make_unique<User>();

	box_ = std::make_unique<BoxEntity>();
	{
		box_->init(CreateEntity(this, "box"));
		box_->addComponent<vst::LuaShaderComponent>();
		auto& geo = box_->addComponent<ns::GeometryComponent>();
		geo.geometry = ns::Geometry::CreateCubeWithNormal();
		auto& instancing = box_->addComponent<ns::BasicLightInstancingMaterial>();
		box_->getComponent<ns::TransformComponent>().transform.scaleXYZ = {40.0f, 40.0f, 40.0f};

		instancing.interop.lightPos = {1500.0f, 1500.0f, 1600.0f};
		block_.resize(length_, std::vector<std::vector<ns::Entity>>(length_, std::vector<ns::Entity>(length_)));

		int halfLength = length_ / 2;
		for (int i = 0; i < length_; ++i)
		{
			for (int j = 0; j < length_; ++j)
			{
				for (int k = 0; k < length_; ++k)
				{
					block_[i][j][k] = instancing.createInstance(this);
					auto& instance = block_[i][j][k];
					instance.getComponent<ns::TransformComponent>().transform.position = {(i - halfLength) * 10.0f, (j - halfLength) * 10.0f,
																						  (k - halfLength) * 10.0f};
					instance.getComponent<ns::TransformComponent>().transform.scaleXYZ = {9.5f, 9.5f, 9.5f};
					instance.getComponent<ns::ColorComponent>().color = {(float) i / length_, 
																		 (float) j / length_,
																		 (float) k / length_, 1.0f};
					instancing.updateInstance(instance);
				}
			}
		}
	}
}

void MainScene::onUpdate()
{
	ns::Scene::onUpdate();
	static bool bIsUpdate = false;
	static sol::state lua;
	if(!bIsUpdate) 
	{
		lua.open_libraries(sol::lib::base, sol::lib::math);
		for (auto& kv : lua["math"].get<sol::table>()) {
		    lua[kv.first.as<std::string>()] = kv.second;
	}
	}

	sol::protected_function pf;
	registry_.view<vst::LuaShaderComponent>().each(
		[&](auto& luaComp)
		{
			if (luaComp.bIsDirty)
			{
				luaComp.bIsDirty = false;
				lua.safe_script("function compute(x,y,z,t) "+ luaComp.luaString + " end", sol::script_pass_on_error);
			}
			auto f = lua.get<sol::function>("compute");
			pf = f;
		}
		);

	if (pf.valid())
	{
		auto& instancingMat = box_->getComponent<ns::BasicLightInstancingMaterial>();	
		int halfLength = length_ / 2;
		for(int x =0; x < length_; ++x)
		{
			for(int y =0; y < length_; ++y)
			{
				for(int z =0; z < length_; ++z)
				{
					auto& instance = block_[x][y][z];
					auto& color = instance.getComponent<ns::ColorComponent>().color;
					sol::protected_function_result pfr = pf(x - halfLength, y - halfLength, z - halfLength, 0);
					if (pfr.valid() && pfr.return_count() == 1 && pfr.get_type(0) == sol::type::number)
					{
						int result = pfr.get<int>();
						if(result <= 0)
						{
							color.r = -1.0f;
						}
						else 
						{
							color.r = palette[result % palette.size()].r;
							color.g = palette[result % palette.size()].g;
							color.b = palette[result % palette.size()].b;
						}
					}
					auto& instancingComponent = instance.getComponent<ns::InstancingComponent<ns::BasicLightInstancingMaterial>>();
					instancingMat.interop.color[instancingComponent.instancingIdx] = {color.r, color.g, color.b, color.a};
				}
			}
		}
		instancingMat.interop.bIsDirty = true;
	}
	bIsUpdate = true;
}

}	 // namespace vst