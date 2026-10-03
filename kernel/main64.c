/* main64 why not */

#include "libc.h"
#include "bootinfo.h"

__attribute__((cdecl,)) void entry64(struct BootInfo *bi){
	(void)bi;
	__asm__ volatile("sti");
	goto end;
end:
	for(;;){while(1){__asm__ volatile("cli; hlt");}}
	return;
}
