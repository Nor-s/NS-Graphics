#include <sol/sol.hpp>
#include <cassert>

struct vars {
    int boop = 0;
};

int main() {
    sol::state lua;
    lua.new_usertype<vars>("vars", "boop", &vars::boop);
    lua.script("beep = vars.new()\n"
               "beep.boop = 1");
    assert(lua.get<vars>("beep").boop == 1);
    std::cout<< "Lua script executed successfully, boop value is: " 
              << lua.get<vars>("beep").boop << std::endl;
}