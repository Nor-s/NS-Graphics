#ifndef _VST_MAIN_SCENE_H_
#define _VST_MAIN_SCENE_H_

#include <memory>
#include <nengine.h>

namespace vst
{
class BoxEntity;

class MainScene : public ns::Scene
{
public:
    MainScene();
    ~MainScene() = default;

    virtual void onUpdate() override final;

private:
    std::unique_ptr<BoxEntity> box_;
    std::vector<std::vector<std::vector<ns::Entity>>> block_;
    int length_{33};

};

};	  // namespace vst

#endif