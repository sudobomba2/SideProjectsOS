#include "libc.h"
#include "vga.h"
#include "stdarg.h"
#include "asm.h"

#include "bootinfo.h"

uint32_t cx=0;
uint32_t cy=0;
uint32_t raw=0;
uint8_t color=0x0F;
uint8_t defcolor=0x1F;

void printk_putuint(unsigned int val,unsigned int base,int upper,int width,int zeropad){
	char buf[32];
	const char *digits=upper?"0123456789ABCDEF":"0123456789abcdef";
	int i=0;
	if(val==0){buf[i++]='0';}
	while(val>0){buf[i++]=digits[val%base];val/=base;}
	while(i<width){buf[i++]=zeropad?'0':' ';}
	while(i>0){putc(buf[--i]);}
	return;
}

void printk_putint(int val,int width,int zeropad){
	unsigned int uval;
	if(val<0){putc('-');uval=(unsigned int)(-val);if(width>0){width--;}}
	else{uval=(unsigned int)val;}
	printk_putuint(uval,10,0,width,zeropad);
	return;
}

void scroll(void){
	int y;
	int x;
	if(cy<H){return;}
	for(y=1;y<H;y++){for(x=0;x<W;x++){VGAMEM[(y-1)*W+x]=VGAMEM[y*W+x];}}
	for(x=0;x<W;x++){VGAMEM[(H-1)*W+x]=(color<<8)|' ';}
	cy=H-1;
	return;
}

void curupd(void){
	uint16_t position=cy*W+cx;
	outport_b(0x3D4,0x0F);
	outport_b(0x3D5,position&0xFF);
	outport_b(0x3D4,0x0E);
	outport_b(0x3D5,(position>>8)&0xFF);
	return;
}

void clrscr(void){
	int i;
	i=0;
	while(i<W*H){VGAMEM[i]=(color<<8)|' ';i++;}
	cx=0;
	cy=1;
	curupd();
	return;
}

void putc(char character){
	int oldcx;
	int oldcy;
	uint8_t oldcolor;
	if(raw==1){color=defcolor;}
	if(character=='\n'){cx=0;cy++;scroll();curupd();return;}
	if(character=='\b'){if(cx>0){cx--;}VGAMEM[cy*W+cx]=(color<<8)|' ';curupd();return;}
	if(character=='\r'){cx=0;curupd();return;}
	if(character=='\t'){uint32_t next=(cx+4)&~3u;while(cx<next){VGAMEM[cy*W+cx]=(color<<8)|' ';cx++;if(cx>=W){cx=0;cy++;scroll();break;}}curupd();return;}
	VGAMEM[cy*W+cx]=(color<<8)|character;
	cx++;
	if(cx>=W){cx=0;cy++;}
	scroll();
	curupd();
	return;
}

void puts(const char *string){
	int i;
	i=0;
	while(string[i]){putc(string[i]);i++;}
	return;
}

void perror(const char *command){
	puts("ERROR: Undefined reference to ");
	puts(command);
	return;
}

void printf(const char *format,...){
	va_list args;
	int width;
	int zeropad;
	va_start(args,format);
	while(*format){
		if(*format!='%'){putc(*format++);continue;}
		format++;
		width=0;
		zeropad=0;
		if(*format=='0'){zeropad=1;format++;}
		while(*format>='0'&&*format<='9'){width=width*10+(*format-'0');format++;}
		switch(*format){
			case 'd':
			case 'i':
				printk_putint(va_arg(args,int),width,zeropad);
				break;
			case 'u':
				printk_putuint(va_arg(args,unsigned int),10,0,width,zeropad);
				break;
			case 'x':
				puts("0x");
				printk_putuint(va_arg(args,unsigned int),16,0,width,zeropad);
				break;
			case 'X':
				puts("0x");
				printk_putuint(va_arg(args,unsigned int),16,1,width,zeropad);
				break;
			case 'p':
				puts("0x");
				printk_putuint((unsigned int)va_arg(args,void*),16,0,8,1);
				break;
			case 's':
				puts(va_arg(args,const char*));
				break;
			case 'c':
				putc((char)va_arg(args,int));
				break;
			case '%':
				putc('%');
				break;
			default:
				putc('%');
				putc(*format);
				break;
		}
		format++;
	}
	va_end(args);
	return;
}