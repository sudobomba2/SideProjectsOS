#!/bin/bash
set -e

# tweak this shit if needed
export CCOMPILER="x86_64-elf"
export AS="nasm"
export CC="$CCOMPILER-gcc"
export LD="$CCOMPILER-ld" 
export OBJCOPY="$CCOMPILER-objcopy"
export CFLAGS="-Wall -Wextra -fno-builtin -nodefaultlibs -nostartfiles -nostdlib -ffreestanding -fno-pic -fno-pie -fno-stack-protector -fno-asynchronous-unwind-tables -nostdinc -mno-red-zone -mno-sse -I./kernel/lib -I./kernel/headers -I./kernel/sys"
export LDFLAGS="-T kernel/linker.ld -m elf_x86_64 -static -nostdlib" 
export OBJFLAGS="-O binary"

build(){ # build
	find . \( -name '*.o' -o -name '*.d' \) -print -exec rm -rf '{}' \;
	rm -rf floppy.img
	nasm -f bin stage1/fat12.s -o BOOT0
	nasm -f elf64 kernel/entry16.s -o entry16.o
	$CC $CFLAGS -c kernel/main64.c -o main64.o
	$CC $CFLAGS -c kernel/lib/libc.c -o libc.o 
	$CC $CFLAGS -c kernel/lib/vga.c -o vga.o 
	$LD $LDFLAGS entry16.o main64.o libc.o vga.o -o KERNEL64.ELF
	$OBJCOPY $OBJFLAGS KERNEL64.ELF KERNEL64
	find . \( -name '*.o' -o -name '*.d' \) -print -exec rm -rf '{}' \;
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	mkfs.fat -F 12 -R 1 -n "BOOT" floppy.img
	dd if=BOOT0 of=floppy.img bs=512 count=1 conv=notrunc
	mcopy -i floppy.img KERNEL64 ::
	rm -rf BOOT0 KERNEL64.ELF KERNEL64
}

build
