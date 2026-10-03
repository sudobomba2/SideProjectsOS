# SideProjects OS
A 64-Bit Operating System that i've been developing secretly

# LICENSE
Idk, maybe i'll choose it later

# Build
Just simply run "bash build.sh"

(If you encountered a error, Just tweak the "build.sh" script)

To clean "bash clean.sh"

# Dependencies and Running the OS

You'll need
- nasm
- GCC (x86_64-elf cross-compile)
- Binutils (x86_64-elf cross-compile)
- dosfstools
- mtools
- QEMU (x86_64 emulate)

Running the OS

Just run:

`qemu-system-x86_64 -m 512M -cpu core2duo -fda floppy.img -boot a -vga std`
