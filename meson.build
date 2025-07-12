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

entt_proj = cmake.subproject('entt')
entt_dep = entt_proj.dependency('EnTT')

# Set GL
gl_dep = declare_dependency(link_args: ['-framework', 'OpenGL'])

dep_list =[
    spdlog_dep,
    sdl2_dep,
    gl_dep,
    imgui_dep,
    entt_dep,
    lua_dep,
]


# Src Files
nsgraphics_src =[
'src/core/common/logger.cpp',
'src/core/common/nsTransform.cpp',

'src/core/scene/nsScene.cpp',
'src/core/entity/actorEntity.cpp',
'src/core/entity/userEntity.cpp',
'src/core/entity/nsEntity.cpp',

'src/core/entity/component/nsMaterial.cpp',
'src/core/entity/component/components.cpp',

'src/core/gpu/geometry.cpp',

'src/core/gpu/gl/glRenderTarget.cpp',
'src/core/gpu/gl/glRenderer.cpp',
'src/core/gpu/gl/glShader.cpp',
'src/core/gpu/gl/glShaderSrc.cpp',
'src/core/gpu/gl/glGeometry.cpp',
'src/core/gpu/gl/glBuffer.cpp',

'src/editor/app.cpp',
'src/editor/event/events.cpp',
'src/editor/event/simpleEventQueue.cpp',
'src/editor/window/SDLWindow.cpp',
'src/editor/window/SDLInputManager.cpp',
'src/editor/imgui/imguiLayer.cpp',
'src/editor/imgui/imguiWindow.cpp',
'src/editor/imgui/imguiTextEditor.cpp',
'src/editor/imgui/imguiSceneWindow.cpp',
'src/editor/imgui/imguiComponents.cpp',
]
nsgraphics_include = include_directories('./src', './src/core', './src/editor')

nsgraphics_dep = declare_dependency(
   dependencies        : dep_list,
   include_directories : nsgraphics_include,
   sources             : nsgraphics_src
)

# Define Lib
ns_graphics_lib = library('ns_graphics', 
    nsgraphics_src,
    dependencies: nsgraphics_dep
)


subdir('src/example/VoxelShaderToy')
subdir('src/example/LuaTest')
subdir('src/example/thorvg')
subdir('src/example/LearnOpengl')
