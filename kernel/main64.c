/* main64 why not */

#include "libc.h"
#include "bootinfo.h"
#include "video.h"

__attribute__((cdecl,)) void entry64(struct BootInfo *bi){
	__asm__ volatile("sti");
	if(video_vesa_init(bi)==0){
		puts("SideProjectsOS 1.00\r\n");
	}else{goto end;}
	goto end;
end:
	for(;;){while(1){__asm__ volatile("cli; hlt");}}
	return;
}
