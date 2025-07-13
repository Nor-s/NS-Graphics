
vst_src = [
    './main.cpp',
    './VST.cpp',
    './Scene/mainScene.cpp',
    './Scene/Entity/user.cpp',
    './Scene/Entity/box.cpp',
]

sol_proj = subproject('sol2')
sol_dep = sol_proj.get_variable('sol2_dep')

# Define Exe
executable('vst', 
    vst_src,
    dependencies: [nsgraphics_dep, sol_dep],
    link_with: ns_graphics_lib
)
