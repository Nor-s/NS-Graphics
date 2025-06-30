#include "userEntity.h"
#include "input/inputController.h"
#include "component/components.h"

namespace ns
{

UserEntity::UserEntity(std::unique_ptr<Entity> entity)
    :entity_(std::move(entity))
{
}

UserEntity::~UserEntity()
{
}

void UserEntity::setupInputController(InputController*)
{
}

}