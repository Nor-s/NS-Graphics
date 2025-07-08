#ifndef _NS_GRAPHICS_CORE_ENTITY_USER_ENTITY_H_
#define _NS_GRAPHICS_CORE_ENTITY_USER_ENTITY_H_

#include "ActorEntity.h"

namespace ns
{
class InputController;

class UserEntity : public ActorEntity
{
public:
    virtual ~UserEntity();
    virtual void setupInputController(InputController*);

protected:
    UserEntity() = default;
};

}	 // namespace ns

#endif