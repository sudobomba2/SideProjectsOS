#ifndef __ASSEMBLY_PORT_IO_FUNCTION_H__
#define __ASSEMBLY_PORT_IO_FUNCTION_H__

#include "stdint.h"
#include "stddef.h"

static inline void outport_b(uint16_t port,uint8_t value){__asm__ volatile("outb %0,%1": :"a"(value),"Nd"(port));return;}
static inline void outport_w(uint16_t port,uint16_t value){__asm__ volatile("outw %0,%1": :"a"(value),"Nd"(port));return;}
static inline void outport_l(uint16_t port,uint32_t value){__asm__ volatile("outl %0,%1": :"a"(value),"Nd"(port));return;}
static inline uint8_t inport_b(uint16_t port){uint8_t return_value;__asm__ volatile("inb %1,%0":"=a"(return_value):"Nd"(port));return return_value;}
static inline uint16_t inport_w(uint16_t port){uint16_t return_value;__asm__ volatile("inw %1,%0":"=a"(return_value):"Nd"(port));return return_value;}
static inline uint32_t inport_l(uint16_t port){uint32_t return_value;__asm__ volatile("inl %1,%0":"=a"(return_value):"Nd"(port));return return_value;}
static inline void outsb(uint16_t port,const void *buffer,size_t count){__asm__ volatile("rep outsb":"+S"(buffer),"+c"(count):"d"(port):"memory");return;}
static inline void outsw(uint16_t port,const void *buffer,size_t count){__asm__ volatile("rep outsw":"+S"(buffer),"+c"(count):"d"(port):"memory");return;}
static inline void outsl(uint16_t port,const void *buffer,size_t count){__asm__ volatile("rep outsl":"+S"(buffer),"+c"(count):"d"(port):"memory");return;}
static inline void insb(uint16_t port,void *buffer,size_t count){__asm__ volatile("rep insb":"+D"(buffer),"+c"(count):"d"(port):"memory");return;}
static inline void insw(uint16_t port,void *buffer,size_t count){__asm__ volatile("rep insw":"+D"(buffer),"+c"(count):"d"(port):"memory");return;}
static inline void insl(uint16_t port,void *buffer,size_t count){__asm__ volatile("rep insl":"+D"(buffer),"+c"(count):"d"(port):"memory");return;}
static inline void io_wait(void){__asm__ volatile("outb %%al, $0x80": :"a"(0));return;}
static inline void io_delay_us(uint32_t us){while(us--){io_wait();io_wait();}return;}
static inline void ASM_CLI(void){__asm__ volatile("cli":::"memory");return;}
static inline void ASM_STI(void){__asm__ volatile("sti":::"memory");return;}
static inline void ASM_HLT(void){__asm__ volatile("hlt":::"memory");return;}
static inline void HANGHALT(void){for(;;){while(1){ASM_CLI();ASM_HLT();}}return;}

#endif

/*
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢠⢰⢰⢢⢢⢰⢠⢀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡌⡎⣎⢮⢺⡸⡕⡧⡳⡱⡕⡕⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢣⡣⡇⣗⢵⢝⣎⢗⣝⢞⡎⡧⡫⡅⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢐⡜⣜⢜⢮⡺⡼⣕⢗⣗⣕⣗⣝⢮⡳⡢⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣇⢧⢫⡺⣪⣺⡪⣗⢧⡳⣕⣗⢗⢵⣟⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⡘⡸⡜⡮⡪⡲⡽⣝⢵⣝⢞⢮⡫⡺⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢣⢪⢺⢸⠎⡎⣎⢯⢮⡳⡕⡽⣕⣗⢭⢫⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⢜⢕⢕⢕⠥⡑⡜⢜⢕⢪⡪⡣⡳⡵⣝⢮⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⡎⡧⡳⡱⡱⡱⣕⢳⢕⠵⣝⢞⢞⡞⠜⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡪⢮⡫⣗⢧⢪⣪⢪⣳⢽⡺⣝⠕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⡳⡹⣮⡻⣜⡮⣳⢯⢯⢯⢎⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⡸⣸⡹⣺⡺⣺⣝⢮⢯⢏⡗⡭⣓⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢱⢱⡣⡯⣺⣪⡳⣝⢽⢕⣗⢭⢺⢸⢢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⡣⡳⣕⣝⢞⢮⣺⡺⣪⢯⣳⣳⣣⢳⡹⡜⣅⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢔⢕⣝⢜⢮⢎⢯⣳⡳⣝⡮⣗⣗⣗⣕⢗⣝⢮⡪⡄⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢰⢸⢸⡱⣪⣫⡫⡯⣳⡳⡽⣮⣻⣺⣺⣺⡪⣗⢧⡳⣕⢕⠄⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡔⡕⡕⡕⡵⡹⣜⢮⢮⡻⡮⣯⣻⣺⣺⣺⣺⣺⡺⡮⡳⣝⢮⢳⢕⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⢄⢔⢜⢜⢜⡜⣜⢎⡗⣝⢮⡫⣗⣯⣻⣺⣺⢞⣞⣞⣞⡮⣯⡫⡯⡮⣳⡣⣏⢇⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⣎⢮⢪⢪⡪⡪⡪⣎⢞⢼⡱⣝⢮⡳⣯⣳⣳⣳⢗⡯⣟⡮⣗⣗⣟⣞⢮⢯⢯⣺⢺⡜⡵⡅⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⡠⣪⢺⢜⢜⢎⢧⡣⣫⢺⢜⣕⢧⣻⡪⣗⣟⣞⡾⡵⡯⣯⢯⣗⡯⣗⡷⣳⢯⢯⢯⣳⣳⡳⣝⢞⢼⠄⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⢐⢎⢮⡳⣝⢼⡱⣣⡫⣎⢮⡳⣕⢷⢵⣝⣞⣞⡾⣽⢽⢯⢯⣟⡾⣽⣳⢯⣗⡯⣯⣳⣳⡳⣽⡪⡯⡮⣫⡀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⢀⢧⡫⡳⣝⢎⢮⢺⡪⡮⡺⣜⣞⢮⢯⣳⣳⣳⢗⡯⣗⡯⡿⣽⣺⢽⣳⢯⣗⡷⣫⣗⣗⣗⣟⢮⢯⡳⣝⣜⢆⠀⠀⠀
*⠀⠀⠀⠀⠀⠠⣝⢮⢮⢯⢮⢣⡫⣺⢪⡳⣝⢮⢮⢯⣳⣳⡳⡯⡯⡯⣗⡯⣟⣗⡯⣟⡾⣽⣺⢽⣳⣳⣳⢷⢽⢽⡳⣝⢮⣪⡳⡀⠀⠀
*⠀⠀⠀⠀⠀⢎⢮⡳⣳⢝⢮⢣⡫⡮⣳⢽⢮⡻⣮⣳⣳⡳⣯⣻⢽⣫⣗⡯⣗⡯⡯⣗⡯⣗⡯⣟⢾⣕⡯⡯⣯⣳⢯⣳⡳⡵⡹⡂⠀⠀
*⠀⠀⠀⠀⢰⡹⣕⢽⡺⡝⡎⡮⢮⡻⡮⡯⣗⣟⣞⣞⢾⣝⡷⡽⣽⡺⡮⡯⣗⡯⣟⡵⡯⣗⡯⣯⡻⡮⣯⣻⣺⣺⣳⡳⡽⡵⡝⡆⠀⠀
*⠀⠀⠀⠀⡪⡺⡼⣕⢯⢪⡺⣜⢷⣝⡯⣯⣗⣗⣗⡯⣟⡮⡯⡯⣗⡯⡯⡯⣗⢯⣗⢯⢯⣗⢯⣗⡯⡯⣗⣗⣗⣗⡷⡽⣝⢮⡫⠂⠀⠀
*⠀⠀⠀⠀⢪⣫⡺⣪⡳⣕⢝⡮⣗⡷⡯⣗⡷⣯⣺⢽⡳⣯⣻⢽⡳⡯⡯⡯⣯⡳⡽⣝⢷⣝⣗⣗⡯⡯⣗⡯⣞⢾⢽⣝⢮⡳⡝⠀⠀⠀
*⠀⠀⠀⠀⢘⢖⡽⡵⡹⣮⡳⣝⡾⡽⣽⡳⣯⣗⡯⣯⣻⣺⣺⢽⢽⢽⢽⢽⢮⢯⣻⡪⣗⣗⣗⣗⡯⡯⣗⡯⡯⡯⣗⡯⣗⠽⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⢳⢽⢽⣝⣗⡯⡷⡽⣝⣗⡯⣗⡷⡯⣗⡯⣞⡾⡽⣽⢽⢽⢽⣝⣗⢷⣝⣞⣞⣞⡮⡯⡯⣗⢯⢯⣻⢵⡫⡏⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠈⠽⣕⣗⡯⣯⢿⣝⣗⡯⡯⣗⡯⣟⣗⡯⣗⡯⣯⣗⡯⡯⣟⣞⢾⣝⣞⣞⣞⢾⢽⢽⢽⣺⣝⣗⡯⡯⡏⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠱⣳⢯⢿⣽⢷⡯⡿⣽⣳⢯⣗⡷⡯⣗⡯⣗⣗⡯⣯⢗⡯⣟⣞⣞⣞⡾⡽⡽⡽⣽⣺⣺⣺⠽⠋⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠘⠯⠛⠽⣻⡽⣯⢗⡯⣟⡾⣽⢽⣳⢯⣗⡯⣟⢾⢽⣺⢵⣳⣳⢗⡯⡯⣯⣻⡺⠊⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠹⡽⣽⢽⡳⡯⣗⣟⡾⣽⣺⢽⣳⢯⣟⡾⣽⣺⢾⢽⣺⠽⠓⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠹⢽⡽⣯⢗⣯⢯⣗⡯⣟⡾⣽⣺⣽⣳⣯⢿⡭⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢽⡇⠀⢈⣩⡭⠍⠉⠛⠛⠙⠞⠟⠾⣻⢿⡽⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣕⡯⣧⢴⡺⠓⠃⠀⠀⠀⠀⠀⠀⠀⠀⠈⡿⡍⠓⠿⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣀⣴⣺⢜⡮⣗⣏⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠝⠀⠀⠈⠹⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⢠⡤⣖⡾⡽⠾⠙⠈⠁⢕⣟⠈⠑⠯⣳⣲⣢⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠁⠀⠀⠀⠀⠀⣣⡳⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⣳⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*/ /* Dove Braille*/