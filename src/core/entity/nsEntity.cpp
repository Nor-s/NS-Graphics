#include "nsEntity.h"
#include "scene/nsScene.h"

namespace ns 
{

Entity::Entity(Scene* scene)
{
    r_scene_ = scene;
   handle_ = scene->registry_.create();
}

}
