#ifndef _NS_GRAPHICS_CORE_SCENE_SCEHE_H_
#define _NS_GRAPHICS_CORE_SCENE_SCEHE_H_

#include <vector>
#include "../entity/entity.h"
#include "../platform/platformEvent.h"

namespace ns
{
class GlRenderTarget;

class Scene
{
    using EntityId = Entity*;
    using Entities = std::vector<EntityId>;

public:
    Scene();
    virtual ~Scene();
    virtual void init(const Resolution& res);
    virtual void resize(const Resolution& res);
    virtual void draw(){};
    uint64_t getSceneImage();
    Resolution getResolution();

    virtual void onUpdate();
    virtual void onRender();

protected:
    int getRenderId() const;

private:
	std::unique_ptr<GlRenderTarget> sceneRenderTarget_;
    std::shared_ptr<CameraEntity> currentCamera_ = nullptr;
    Entities entities_;
    // std::shared_ptr<PlayerEntity> player_ = nullptr;
};

}	 // namespace ns

#endif