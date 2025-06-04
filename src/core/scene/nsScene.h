#ifndef _NS_GRAPHICS_CORE_SCENE_SCEHE_H_
#define _NS_GRAPHICS_CORE_SCENE_SCEHE_H_

#include <vector>
#include "entity.h"
#include "../platform/platformEvent.h"
#include "../gpu/gpu.h"

namespace ns
{
class Scene
{
    using EntityId = Entity*;
    using Entities = std::vector<EntityId>;

public:
    Scene();
    virtual ~Scene() = default;
    void init(const Resolution& res);
    void draw(const SystemIO& io);
    uint64_t getSceneImage();
    Resolution getResolution();

private:
	std::unique_ptr<RenderTarget> sceneRenderTarget_;
    std::shared_ptr<CameraEntity> currentCamera_ = nullptr;
    Entities entities_;
    Entities drawList_;
    // std::shared_ptr<PlayerEntity> player_ = nullptr;
};

}	 // namespace ns

#endif