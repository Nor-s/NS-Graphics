tvgex_src = [
    './main.cpp',
    './tvg.cpp',
    './imguiTvgWindow.cpp',
]

tvg_proj = subproject('thorvg', default_options:['engines=sw,gl', 'default_library=shared', 'loaders=all' ])
tvg_dep = tvg_proj.get_variable('thorvg_dep')
tvg_lib = tvg_proj.get_variable('thorvg_lib')

# thorvg_dep, 
tvgex_dep = [spdlog_dep, imgui_dep, tvg_dep, entt_dep]

# Define Exe
executable('tvg', 
    tvgex_src,
    dependencies: tvgex_dep,
    include_directories: nsgraphics_include,
    link_with: [tvg_lib, ns_graphics_lib]
)
