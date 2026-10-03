ENTRY(start)
SECTIONS {
	. = 0x8000;
	__kernel_start = .;
	.text : { *(.text.entry) *(.text .text.*) }
	.rodata : { *(.rodata*) }
	.data : { *(.data*) }
	.bss : { __bss_start = .; *(COMMON) *(.bss*)  __bss_end = .; }
	__kernel_end = .;
	ASSERT(__kernel_end<0x70000,"kernel image too large for low memory")
}
