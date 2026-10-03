#include "video.h"
#include "stddef.h"
#include "font8x8.h"
#include "libc.h"

#define SCREEN_W 640
#define SCREEN_H 480
#define CELL 8
#define COLS (SCREEN_W/CELL)
#define ROWS (SCREEN_H/CELL)

uint32_t Column;
uint32_t Rows;
uint32_t CurrentX;
uint32_t CurrentY;
uint32_t FGColor=0x00FFFFFF;
uint32_t BGColor=0x00000000;

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
	VideoMode.Base=(volatile uint8_t*)(uintptr_t)v->Framebuffer;
	VideoMode.Width=v->Width;
	VideoMode.Height=v->Height;
	VideoMode.Pitch=v->Pitch;
 	VideoMode.BPP=v->BPP;
	FramebufferBase=(volatile uint8_t*)(uintptr_t)v->Framebuffer;
	Column=VideoMode.Width/CELL;
	Rows=VideoMode.Height/CELL;
	CurrentX=0;
	CurrentY=0;
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

static void draw_glyph(uint32_t cx,uint32_t cy,char c){
	const char *glyph=font8x8_basic[(uint8_t)c&0x7F];
	for(uint32_t row=0; row<8;row++){uint32_t *dst=(uint32_t*)video_vesa_row(cy*CELL+row)+cx*CELL;uint8_t bits=(uint8_t)glyph[row];for(uint32_t col = 0; col < 8; col++){dst[col]=((bits>>col)&1)?FGColor:BGColor;}}
	return;
}

static void scroll(void){
	size_t line_bytes=(size_t)CELL*VideoMode.Pitch;
	memmove(video_vesa_row(0),video_vesa_row(CELL),(Rows-1)*line_bytes);
	uint8_t *last=video_vesa_row((Rows-1)*CELL);
	if(BGColor==0){memset(last, 0, line_bytes);}
	else{for(uint32_t y=0;y<CELL;y++){uint32_t *row=(uint32_t*)(last+(size_t)y*VideoMode.Pitch);for(uint32_t x=0;x<VideoMode.Width;x++){row[x]=BGColor;}}}
}

static void newline(void) {
	CurrentX=0;
	if(++CurrentY>=Rows){scroll();CurrentY=Rows-1;}
	return;
}

void putc(char character){
	switch(character){
		case '\n': newline();return;
		case '\r': CurrentX=0;return;
		case '\b': if(CurrentX){CurrentX--;draw_glyph(CurrentX,CurrentY,' ');}return;
	}
	draw_glyph(CurrentX,CurrentY,character);
	if(++CurrentX>=Column){newline();}
	return;
}

void puts(const char *string){
	int i=0;
	while(string[i]){putc(string[i]);i++;}
	return;
}
