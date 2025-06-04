#ifndef _NS_GRAPHICS_CORE_INPUT_INPUT_ACTION_H_
#define _NS_GRAPHICS_CORE_INPUT_INPUT_ACTION_H_

#include "input.h"

namespace ns
{

class InputAction
{
public:
	InputAction(InputType type) : type_(type)
	{
	}
	InputType getType() const 
	{
		return type_;
	}

protected:

private:
	InputType type_;
};

}	 // namespace ns

#endif