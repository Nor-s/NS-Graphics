project('NS-Graphics', 'cpp',
    default_options:['cpp_std=c++23']
)

# For Dependency
cmake = import('cmake')
spdlog_dep = dependency('spdlog', required: true)
sdl2_dep = dependency('sdl2')
imgui_dep = cmake.subproject('imgui').dependency('imgui')
lua_proj = subproject('lua')
lua_dep = lua_proj.get_variable('lua_dep')

thorvg_proj = subproject('thorvg', default_options:['engines=sw,gl'])
thorvg_dep = thorvg_proj.get_variable('thorvg_dep')


# Set GL
gl_dep = declare_dependency(link_args: ['-framework', 'OpenGL'])

if not gl_dep.found()
    gl_dep = dependency('GLESv3', required: false)
endif
if not gl_dep.found()
    gl_dep = dependency('GL', required: false)
endif
if not gl_dep.found()
    gl_dep = meson.get_compiler('cpp').find_library('GL', required: false)
endif
if not gl_dep.found()
    gl_dep = dependency('GLESv3', required: false)
endif
if not gl_dep.found()
    gl_dep = meson.get_compiler('cpp').find_library('GLESv3')       
endif

nsgraphics_dep =[
    spdlog_dep,
    sdl2_dep,
    gl_dep,
    imgui_dep,
    lua_dep,
    thorvg_dep
]


# Src Files
nsgraphics_src =[
'src/core/common/logger.cpp',

'src/core/gpu/gl/glRenderTarget.cpp',
'src/core/gpu/gl/glShader.cpp',
'src/core/gpu/gl/glGeometry.cpp',
'src/core/gpu/gl/glBuffer.cpp',

'src/editor/app.cpp',
'src/editor/window/SDLWindow.cpp',
'src/editor/imgui/imguiLayer.cpp',
'src/editor/imgui/imguiWindow.cpp',
'src/editor/imgui/imguiTextEditor.cpp',
'src/editor/imgui/imguiSceneWindow.cpp',
]

nsgraphics_dep = declare_dependency(
   dependencies        : nsgraphics_dep,
   include_directories : include_directories('./src', './src/core', './src/editor'),
   sources             : nsgraphics_src
)

# Define Exe
ns_graphics_lib = library('ns_graphics', 
    nsgraphics_src,
    dependencies: nsgraphics_dep
)


subdir('src/example/VoxelShaderToy')
subdir('src/example/LuaTest')
subdir('src/example/thorvg')
subdir('src/example/LearnOpengl')
