#ifndef __SIDEPROJECTS_VGA_UTILITY_H__
#define __SIDEPROJECTS_VGA_UTILITY_H__
#pragma once

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"
#include "stdarg.h"

extern uint32_t cx;
extern uint32_t cy;
extern uint32_t raw;
extern uint8_t color;
extern uint8_t defcolor;

void printk_putuint(unsigned int val,unsigned int base,int upper,int width,int zeropad);
void printk_putint(int val,int width,int zeropad);
void clrscr(void);
void curupd(void);
void scroll(void);
void putc(char character);
void puts(const char *string);
void perror(const char *command);
void printf(const char *format,...);

#endif