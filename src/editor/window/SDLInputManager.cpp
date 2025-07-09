#include "SDLInputManager.h"

#include <cstring>

namespace ns
{

SDLInputManager::SDLInputManager()
{
    init();
}

void SDLInputManager::init() 
{
    memset(inputs, 0, sizeof inputs);
}

}
