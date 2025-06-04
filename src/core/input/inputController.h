#ifndef _NS_GRAPHICS_CORE_INPUT_INPUT_CONTROLLER_H_
#define _NS_GRAPHICS_CORE_INPUT_INPUT_CONTROLLER_H_

#include <memory>
#include <vector>
#include <unordered_map>

#include "inputAction.h"

namespace ns
{

class InputActionBinding
{
public:
    InputActionBinding(const InputAction& action, InputTrigger triggerState)
    : action_(action), trigger_(triggerState)
    {
    }
	virtual void execute(const InputValue& inputValue) = 0;

    InputTrigger getInputTrigger()
    {
        return trigger_;
    }

private:
    const InputAction& action_;
    InputTrigger trigger_;
};

template<typename Func>
class InputActionFunctionBinding : public InputActionBinding
{
public:
    InputActionFunctionBinding(Func func, const InputAction& action, InputTrigger triggerState)
    :InputActionBinding(action, triggerState), func_(func) 
    {
    }

    virtual void execute(const InputValue& inputValue) override
    {
        func_(inputValue);
    }

private:
    Func func_;
};

template<typename TClass, typename Func>
class InputActionMemberFunctionBinding : public InputActionBinding
{
public:
    InputActionMemberFunctionBinding(TClass* classPointer, Func func, const InputAction& action, InputTrigger triggerState)
    :InputActionBinding(action, triggerState), classPointer_(classPointer), func_(func) 
    {
    }

    virtual void execute(const InputValue& inputValue) override
    {
        (classPointer_->*func_)(inputValue);
    }

private:
    TClass* classPointer_;
    Func func_;
};


class InputController
{
public:
    template<typename TClass>
    void bindAction(const InputAction& action, InputTrigger triggerState, TClass* object, void (TClass::*func)(const InputValue& inputValue))
    {
        auto* actionEvent = new InputActionMemberFunctionBinding<TClass, decltype(func)>(object, func, action, triggerState);
        inputActions_[action.getType()].emplace_back(actionEvent);
    }
    void bindAction(const InputAction& action, InputTrigger triggerState, void (*func)(const InputValue& inputValue))
    {
        auto* actionEvent = new InputActionFunctionBinding<decltype(func)>(func, action, triggerState);
        inputActions_[action.getType()].emplace_back(actionEvent);
    }
    void broadcast(InputType inputType, InputTrigger triggerState, const InputValue& value)
    {
        for(auto& inputActionBinding : inputActions_[inputType])
        {
            if(HasFlag(inputActionBinding->getInputTrigger(), triggerState))
            {
                inputActionBinding->execute(value);
            }
        }
    }

private:
	std::unordered_map<InputType, std::vector<InputActionBinding*>> inputActions_;
};

}	 // namespace ns

#endif