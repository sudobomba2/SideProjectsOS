# SideProjects OS
A Operating System that i've been developing secretly

# LICENSE
Idk, maybe i'll choose it later

# Build
Just simply run "bash build.sh"

(If you encountered a error, Just tweak the "build.sh" script)

# Dependencies and Running the OS

You'll need
- nasm
- GCC (x86_64-elf cross-compile)
- Binutils (x86_64-elf cross-compile)
- dosfstools
- mtools
- QEMU (x86_64)

Running the OS

`qemu-system-x86_64 -cpu core2duo -fda floppy.img -boot a`
