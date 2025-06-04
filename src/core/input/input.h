#ifndef _NS_GRAPHICS_CORE_INPUT_INPUT_H_
#define _NS_GRAPHICS_CORE_INPUT_INPUT_H_

#include "../common/nsVector.h"

namespace ns
{

enum class InputType : uint8_t
{
	MOUSE_LEFT_DOWN = 0u,
    MOUSE_WHEEL,
    SIZE
};

enum class InputTrigger : uint8_t
{
    Started = 1 << 1, 
    Triggered = 1 << 2, 
    Ended = 1 << 3
};

inline InputTrigger operator|(InputTrigger a, InputTrigger b) {
    return static_cast<InputTrigger>(
        static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline InputTrigger operator&(InputTrigger a, InputTrigger b) {
    return static_cast<InputTrigger>(
        static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline bool HasFlag(InputTrigger value, InputTrigger flag) {
    return (static_cast<uint8_t>(value) & static_cast<uint8_t>(flag)) != 0;
}

class InputValue
{
public:
    InputValue(float x)
    : value_(x, 0.0f, 0.0f)
    {
    }
    InputValue(float x, float y)
    : value_(x, y, 0.0f)
    {
    }
    InputValue(float x, float y, float z)
    : value_(x, y, z)
    {
    }
    template<typename T>
    T get() const
    {
        return static_cast<T>(value_);
    }

private:
    ns::Vec3 value_;
};

}	 // namespace ns

#endif