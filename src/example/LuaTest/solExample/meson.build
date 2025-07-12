solExample_src = [
    './main.cpp'
]


sol_proj = subproject('sol2')
sol_dep = sol_proj.get_variable('sol2_dep')

# Define Exe
executable('solExample', 
    solExample_src,
    dependencies: sol_dep,
)
