#include "libc.h"
#include "bootinfo.h"
#include "vga.h"

__attribute__((cdecl,)) void entry64(struct BootInfo *bi){
	__asm__ volatile("sti");
	clrscr();
	printf("KERNEL64\r\n");
	goto end;
end:
	for(;;){while(1){__asm__ volatile("cli; hlt");}}
	return;
}
