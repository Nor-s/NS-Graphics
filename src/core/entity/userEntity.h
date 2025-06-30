#ifndef _NS_GRAPHICS_CORE_ENTITY_USER_ENTITY_H_
#define _NS_GRAPHICS_CORE_ENTITY_USER_ENTITY_H_

#include <memory>
#include "nsEntity.h"

namespace ns
{
class InputController;

class UserEntity 
{
public:
    virtual ~UserEntity();
    virtual void setupInputController(InputController*);

protected:
    UserEntity(std::unique_ptr<Entity> entity);
    std::unique_ptr<Entity> entity_;
};

}	 // namespace ns

#endif