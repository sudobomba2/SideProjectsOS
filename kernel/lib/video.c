#include "video.h"
#include "stddef.h"

#define PDPT_ADDR 0x2000
#define PAGE_2M  0x200000ULL
#define PD_FLAGS (0x83ULL|0x10ULL)
#define FB_PD_MAX 4

struct VideoFramebuffer VideoMode;
volatile uint8_t *FramebufferBase;

static uint64_t PD[FB_PD_MAX][512]__attribute__((aligned(4096)));
static int PDUsed;

static int map_2m(uint64_t phys){
	uint64_t *pdpt=(uint64_t*)(uintptr_t)PDPT_ADDR;
	unsigned pi=(unsigned)((phys>>30)&511);
	unsigned di=(unsigned)((phys>>21)&511);
	if(!(pdpt[pi]&1)){if(PDUsed>=FB_PD_MAX){return -1;}pdpt[pi]=(uint64_t)(uintptr_t)PD[PDUsed++]|3;}
	uint64_t *pd=(uint64_t*)(uintptr_t)(pdpt[pi]&~0xFFFULL);
	pd[di]=phys|PD_FLAGS;
	return 0;
}

static int map_range(uint64_t phys,uint64_t size){
	uint64_t a=phys&~(PAGE_2M-1);
	uint64_t end=(phys+size+PAGE_2M-1)&~(PAGE_2M-1);
	for(;a<end;a+=PAGE_2M){if(map_2m(a)!=0){return -1;}}
	__asm__ volatile("mov %%cr3,%%rax\n\tmov %%rax,%%cr3":::"rax","memory");
	return 0;
}

int video_vesa_init(const struct BootInfo *bi){
	const struct VBEInfo *v=&bi->Video;
	FramebufferBase=NULL;
	if(v->Width==0||v->Height==0||v->BPP!=32||v->Framebuffer==0){return -1;}
	if(map_range(v->Framebuffer,(uint64_t)v->Pitch*v->Height)!=0){return -1;}
	VideoMode.Width=v->Width;
	VideoMode.Height=v->Height;
	VideoMode.Pitch=v->Pitch;
 	VideoMode.BPP=v->BPP;
	FramebufferBase=(volatile uint8_t *)(uintptr_t)v->Framebuffer;
	return 0;
}

int video_vesa_available(void){return FramebufferBase!=NULL;}
const struct VideoFramebuffer *video_vesa_get_mode(void){return &VideoMode;}

void video_vesa_clear(uint32_t rgb){(void)rgb;return;}
void video_vesa_draw_pixel(uint32_t x,uint32_t y,uint32_t rgb){
	if(!FramebufferBase||x>=VideoMode.Width||y>=VideoMode.Height){return;}
	*(volatile uint32_t*)(FramebufferBase+(size_t)y*VideoMode.Pitch+(size_t)x*4)=rgb;
	return;
}
