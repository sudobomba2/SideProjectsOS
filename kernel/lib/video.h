#ifndef __SIDEPROJECTS_VIDEO_VESAVBE_3_0_H__
#define __SIDEPROJECTS_VIDEO_VESAVBE_3_0_H__
#pragma once

#include "stdint.h"
#include "bootinfo.h"

#define RGB(red,green,blue) ((uint32_t)(((uint32_t)(red)<<16)|((uint32_t)(green)<<8)|(uint32_t)(blue)))

extern uint32_t Column;
extern uint32_t Rows;
extern uint32_t CurrentX;
extern uint32_t CurrentY;
extern uint32_t FGColor;
extern uint32_t BGColor;

extern struct VideoFramebuffer VideoMode;
extern volatile uint8_t *FramebufferBase;

int video_vesa_init(const struct BootInfo *bi);
int video_vesa_available(void);
const struct VideoFramebuffer *video_vesa_get_mode(void);

void video_vesa_clear(uint32_t rgb);
void video_vesa_draw_pixel(uint32_t x,uint32_t y,uint32_t rgb);

static inline uint8_t *video_vesa_row(uint32_t y){return (uint8_t*)VideoMode.Base+(size_t)y*VideoMode.Pitch;}

void putc(char character);
void puts(const char *string);

#endif
