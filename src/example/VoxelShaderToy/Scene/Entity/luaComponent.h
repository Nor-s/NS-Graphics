#ifndef _VST_LUA_COMPONENT_H_
#define _VST_LUA_COMPONENT_H_

#include <string>
#include <sol/sol.hpp>

namespace vst
{

struct LuaShaderComponent
{
	std::string luaString = R"(
        return x + y
    )";
    bool bIsDirty = true;
};

}	 // namespace vst

#endif