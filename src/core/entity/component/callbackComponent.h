#ifndef _NS_GRAPHICS_CORE_ENTITY_COMPONENT_CALLBACK_COMPONENT_H_
#define _NS_GRAPHICS_CORE_ENTITY_COMPONENT_CALLBACK_COMPONENT_H_

#include <memory>

namespace ns
{

class CallbackEvent
{
public:
    virtual void invoke() = 0;
};

template<typename Func>
class LambdaCallbackEvent : public CallbackEvent
{
public:
    LambdaCallbackEvent(Func func)
    : func_(func)
    {
    }
    virtual void invoke() override 
    {
        func_();
    }

private:
    Func func_;
};

template<typename TClass, typename Func>
class MemberFuncCallbackEvent : public CallbackEvent
{
public:
    MemberFuncCallbackEvent(TClass* instance, Func func)
    : instance_(instance), func_(func)
    {
    }
    virtual void invoke() override 
    {
        (instance_->*func_)();  
    }

private:
    TClass* instance_;
    Func func_;
};

template<typename F>
auto CreateLambdaCallback(F&& f) {
    using FnType = std::decay_t<F>;
    return std::make_unique<LambdaCallbackEvent<FnType>>(std::forward<F>(f));
}

struct InitializeCallback
{
    InitializeCallback(std::unique_ptr<CallbackEvent> event)
    : callbackEvent(std::move(event)){}
    std::unique_ptr<CallbackEvent> callbackEvent;
};
struct ActivateCallback
{
    std::unique_ptr<CallbackEvent> callbackEvent;
};
struct UpdateCallback
{
    std::unique_ptr<CallbackEvent> callbackEvent;
};
struct DeactiveCallback
{
    std::unique_ptr<CallbackEvent> callbackEvent;
};
struct DestroyCallback
{
    std::unique_ptr<CallbackEvent> callbackEvent;
};

}	 // namespace ns

#endif