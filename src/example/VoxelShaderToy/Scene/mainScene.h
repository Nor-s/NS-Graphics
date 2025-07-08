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

private:
    std::unique_ptr<BoxEntity> box_;
};

};	  // namespace vst

#endif