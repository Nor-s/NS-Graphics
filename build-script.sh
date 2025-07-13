export PATH="/opt/homebrew/bin:$PATH"

meson setup builddir --buildtype=release

meson compile -C builddir