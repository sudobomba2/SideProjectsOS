#ifndef __SIDEPROJECTS_VIDEO_VESAVBE_3_0_H__
#define __SIDEPROJECTS_VIDEO_VESAVBE_3_0_H__
#pragma once

#include "stdint.h"
#include "bootinfo.h"

#define RGB(red,green,blue) ((uint32_t)(((uint32_t)(red)<<16)|((uint32_t)(green)<<8)|(uint32_t)(blue)))

extern struct VideoFramebuffer VideoMode;
extern volatile uint8_t *FramebufferBase;

int video_vesa_init(const struct BootInfo *bi);
int video_vesa_available(void);
const struct VideoFramebuffer *video_vesa_get_mode(void);

void video_vesa_clear(uint32_t rgb);
void video_vesa_draw_pixel(uint32_t x,uint32_t y,uint32_t rgb);

#endif
