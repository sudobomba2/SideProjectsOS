#ifndef __SIDEPROJECTS_BOOTINFO_H_
#define __SIDEPROJECTS_BOOTINFO_H_
#pragma once

#include "stdint.h"

#pragma pack(push,1)
struct E820Entry{
	uint64_t Base;
	uint64_t Length;
	uint32_t Type;
	uint32_t ACPI;
}__attribute__((packed));
struct BootInfo{
	uint8_t BootDrive;
	uint8_t Padding0;
	uint16_t BootPartitionOffset;
	uint16_t BootPartitionSegment;
	uint16_t Padding1;
	uint32_t E820Count;
	uint32_t Reserved;
	struct E820Entry Memory[];
}__attribute__((packed));
#pragma pack(pop)
#define VGAMEM ((volatile uint16_t*)0xB8000)
#define W 80
#define H 25

#endif