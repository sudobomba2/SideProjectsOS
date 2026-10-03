/* main64 why not */

#include "libc.h"
#include "bootinfo.h"
#include "video.h"

__attribute__((cdecl,)) void entry64(struct BootInfo *bi){
	__asm__ volatile("sti");
	if(video_vesa_init(bi)==0){
		video_vesa_draw_pixel(5,5,RGB(255,255,255));
	}else{goto end;}
	goto end;
end:
	for(;;){while(1){__asm__ volatile("cli; hlt");}}
	return;
}
