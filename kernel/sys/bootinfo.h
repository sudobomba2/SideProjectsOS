#ifndef __SIDEPROJECTS_BOOTINFO_H_
#define __SIDEPROJECTS_BOOTINFO_H_
#pragma once

#include "stdint.h"
#include "stddef.h"

#pragma pack(push,1)
struct E820Entry{
	uint64_t Base;
	uint64_t Length;
	uint32_t Type;
	uint32_t ACPI;
}__attribute__((packed));
struct VBEInfo{
	uint16_t Mode;
	uint16_t Width;
	uint16_t Height;
	uint16_t Pitch;
	uint8_t BPP;
	uint8_t Padding0;
	uint16_t Padding1;
	uint32_t Framebuffer;
}__attribute__((packed));
struct BootInfo{
	uint8_t BootDrive;
	uint8_t Padding0;
	uint16_t BootPartitionOffset;
	uint16_t BootPartitionSegment;
	uint16_t Padding1;
	uint32_t E820Count;
	uint32_t Reserved;
	struct E820Entry Memory[64];
	struct VBEInfo Video;
}__attribute__((packed));
#pragma pack(pop)
struct VideoFramebuffer{
	volatile uint8_t *Base;
	uint32_t Width;
	uint32_t Height;
	uint32_t Pitch;
	uint32_t BPP;
};

_Static_assert(offsetof(struct BootInfo,Memory)==0x10,"E820_BUF mismatch");
_Static_assert(offsetof(struct BootInfo,Video)==0x610,"VBERES mismatch");
_Static_assert(sizeof(struct VBEInfo)==16,"VBEInfo size");

#endif
