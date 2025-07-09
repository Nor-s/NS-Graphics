#ifndef _NS_GRAPHICS_EDITOR_WINDOW_SDL_INPUT_MANAGER_H_
#define _NS_GRAPHICS_EDITOR_WINDOW_SDL_INPUT_MANAGER_H_

#include <core/input/input.h>

namespace ns
{

class SDLInputManager
{
    friend class SDLWindow;

public:
    SDLInputManager();
    void init();

private:
    InputTrigger inputs[InputType::INPUT_TYPE_SIZE];
};

}	 // namespace ns

#endif