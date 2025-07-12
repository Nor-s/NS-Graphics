simple_src = [
    './main.cpp'
]

rawlua_proj = subproject('lua')
rawlua_dep = rawlua_proj.get_variable('lua_dep')



# Define Exe
executable('simpleLua', 
    simple_src,
    dependencies: rawlua_dep,
)
