project('NS-Graphics', 'cpp',
    default_options:['cpp_std=c++20']
)

# For Dependency
cmake = import('cmake')
sglib_cmake = cmake.subproject('sglib')
sglib_dep = sglib_cmake.dependency('sglib').as_link_whole()
spdlog_dep = dependency('spdlog', required: true)
sdl2_dep = dependency('sdl2')
imgui_dep = cmake.subproject('imgui').dependency('imgui')



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
    sglib_dep,
    spdlog_dep,
    sdl2_dep,
    gl_dep,
    imgui_dep
]


# Src Files
src_file =[
'src/editor/main.cpp',
'src/editor/app.cpp',
'src/editor/window/SDLWindow.cpp',
'src/editor/imgui/imguiLayer.cpp',
]

nsgraphics_dep = declare_dependency(
   dependencies        : nsgraphics_dep,
   include_directories : include_directories('./src', './src/core', './src/editor'),
   sources             : src_file
)

# Define Exe
executable('NS-Graphics', 
    src_file,
    dependencies: nsgraphics_dep
)

