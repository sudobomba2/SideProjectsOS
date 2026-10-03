/* main64 why not */

#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x57
#define KEY_F12 0x58
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define ESC 27
#define LINE_MAX 1024
#define ARG_MAX 256

#include "libc.h"
#include "bootinfo.h"
#include "video.h"
#include "asm.h"
#include "gdt.h"
#include "cmos.h"

const char Keymap[128]={
	0,ESC,'1','2','3','4','5','6',
	'7','8','9','0','-','=','\b','\t',
	'q','w','e','r','t','y','u','i',
	'o','p','[',']','\n',0,'a','s',
	'd','f','g','h','j','k','l',';',
	'\'','`',0,'\\', 'z','x','c','v',
	'b','n','m',',','.','/',0,'*',
	0,' ',0
};
const char Shiftmap[128]={
	0,ESC,'!','@','#','$','%','^',
	'&','*','(',')','_','+','\b','\t',
	'Q','W','E','R','T','Y','U','I',
	'O','P','{','}','\n',0,'A','S',
	'D','F','G','H','J','K','L',':',
	'"','~',0,'|','Z','X','C','V',
	'B','N','M','<','>','?',0,'*',
	0,' ',0
};

int shift=0;
int ctrl=0;
int alt=0;
int ext=0;

int getch(void);
void reboot(void);
size_t readline(char *buffer,size_t max);
int tokenize(char *line,char **argv,int max);
void shell(void);

void entry64(struct BootInfo *bi){
	gdt_init();
	if(video_vesa_init(bi)==0){
		puts("SideProjectsOS 1.00\r\n");
		putc('\n');
		shell();
	}else{goto end;}
	goto end;
end:
	for(;;){while(1){__asm__ volatile("cli; hlt");}}
	return;
}

int getch(void){
	uint8_t scancodes;
	char characters;
	uint8_t status=inport_b(0x64);
	if(!(status&1)){return 0;}
	scancodes=inport_b(0x60);
	if(status&0x20){return 0;} 
	if(scancodes==0xE0){ext=1;return 0;}
	if(ext){
		ext=0;
		if(scancodes==0x1D){ctrl=1;return 0;}
		if(scancodes==0x9D){ctrl=0;return 0;}
		if(scancodes==0x38){alt=1;return 0;}
		if(scancodes==0xB8){alt=0;return 0;}
		if(scancodes==0x53){return 0;}
		if(scancodes==0x48){return KEY_UP;}
		if(scancodes==0x50){return KEY_DOWN;}
		if(scancodes==0x4B){return KEY_LEFT;}
		if(scancodes==0x4D){return KEY_RIGHT;}
		return 0;
	}
	if(scancodes==0x01){return ESC;}
	if(scancodes==0x38){alt=1;return 0;}
	if(scancodes==0xB8){alt=0;return 0;}
	if(scancodes==42||scancodes==54){shift=1;return 0;}
	if(scancodes==170||scancodes==182){shift=0;return 0;}
	if(scancodes==29){ctrl=1;return 0;}
	if(scancodes==157){ctrl=0;return 0;}
	if(scancodes&0x80){return 0;}
	if((scancodes>=KEY_F1&&scancodes<=KEY_F10)||scancodes==KEY_F11||scancodes==KEY_F12){return 0;}
	if(scancodes>=128){return 0;}
	if(shift){characters=Shiftmap[scancodes];}
	else{characters=Keymap[scancodes];}
	if(ctrl&&characters>='a'&&characters<='z'){return characters-'a'+1;}
	if(ctrl&&characters>='A'&&characters<='Z'){return characters-'A'+1;}
	return characters;
}

void reboot(void){
	uint8_t good;
	__asm__ volatile("cli");
	do{good=inport_b(0x64);if(good&1){inport_b(0x60);}}while(good&2);
	outport_b(0x64,0xFE);
	io_wait();
	outport_b(0xCF9,0x02);
	io_wait();
	outport_b(0xCF9,0x06);
	io_wait();
	outport_b(0x92,inport_b(0x92)|1);
 	io_wait();
	struct{uint16_t Limit;uint64_t Base;}__attribute__((packed)) idt={0,0};
 	__asm__ volatile("lidt %0": :"m"(idt));
 	__asm__ volatile("int3");
	for(;;){while(1){__asm__ volatile("hlt");}}
	return;
}

size_t readline(char *buffer,size_t max){
	size_t RAHH=0;
	for(;;){
		int key=getch();
		if(key=='\n'){putc('\n');break;}
		if(key=='\r'){putc('\r');break;}
		if(key=='\b'||key==0x7F){if(RAHH){RAHH--;puts("\b \b");}continue;}
		if(key>=32&&key<127&&RAHH<max-1){buffer[RAHH++]=(char)key;putc((char)key);}
	}
	buffer[RAHH]=0;
	return RAHH;
}
int tokenize(char *line,char **argv,int max){
	int argc=0;
	while(*line&&argc<max){
		while(*line==' '){*line++=0;}
		if(!*line){break;}
		argv[argc++]=line;
		while(*line&&*line!=' '){line++;}
	}
	return argc;
}
void shell(void){
	char line[LINE_MAX];
	char *argv[ARG_MAX];
	putc('\n');
	for(;;){
		puts("($) ");
		if(!readline(line,sizeof line)){continue;}
		int argc=tokenize(line,argv,ARG_MAX);
		if(!argc){continue;}
		if(streq(argv[0],"reboot")){reboot();return;}
		else{puts("Unknown Command: ");puts(argv[0]);putc('\n');}
	}
	return;
}
