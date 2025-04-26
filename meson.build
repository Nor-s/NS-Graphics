project('NS-Graphics', 'cpp',
default_options:['cpp_std=c++20']
)

cmake = import('cmake')
sglib_cmake = cmake.subproject('sglib')
sglib_dep = sglib_cmake.dependency('sglib')
spdlog_dep = dependency('spdlog', required: true)

src_file =[
'src/main.cpp'
]

NSGraphics_dep =[
    sglib_dep,
    spdlog_dep
]

executable('NS-Graphics', 
    src_file,
    dependencies: NSGraphics_dep
)

