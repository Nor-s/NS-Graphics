#include <iostream>
#include <string>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

bool CheckLua(lua_State *L, int r)
{
	if (r != LUA_OK)
	{
		std::string errorMessage = lua_tostring(L, -1);
		std::cout << errorMessage << std::endl;
		return false;
	}
	return true;
}

int main()
{
	lua_State* L = luaL_newstate();

	// Add standard libraries to Lua Virtual Machine
	luaL_openlibs(L);

    std::string luaString="a = 1";

    if(CheckLua(L, luaL_dostring(L, luaString.c_str())))
    {
        lua_getglobal(L,"a");
        if(lua_isnumber(L,-1))
        {
            std::cout<< (int)lua_tointeger(L, -1) << std::endl;
        }
    }

    lua_close(L);
}