meson setup builddir --buildtype=debug --default-library=static  -Doptimization=1

meson compile -C builddir
