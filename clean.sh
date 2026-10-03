#!/bin/bash
set -e

find . \( -name '*.o' -o -name '*.d' \) -print -exec rm -rf '{}' \;
rm -rf *.o *.O *.d *.D
rm -rf *.ELF *.elf
rm -rf BOOT0 KERNEL64.ELF KERNEL64 floppy.img
