ENTRY(start)
SECTIONS {
	. = 0x8000;
	.text : { *(.text.entry) *(.text .text.*) }
	.rodata : { *(.rodata*) }
	.data : { *(.data*) }
	.bss : { __bss_start = .; *(COMMON) *(.bss*) __bss_end = .; }
}