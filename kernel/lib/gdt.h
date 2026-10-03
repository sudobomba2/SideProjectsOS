#ifndef __SIDEPROJECTS_GLOBAL_DESCRIPTOR_TABLE_H__
#define __SIDEPROJECTS_GLOBAL_DESCRIPTOR_TABLE_H__
#pragma once

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

#define GDT_NULL_SEGMENT 0x00
#define GDT_CODE32_SEGMENT 0x08
#define GDT_DATA32_SEGMENT 0x10
#define GDT_CODE64_SEGMENT 0x18
#define GDT_DATA64_SEGMENT 0x20
#define GDT_USER_DATA64_SEGMENT 0x28
#define GDT_USER_CODE64_SEGMENT 0x30
#define GDT_TSS_SEGMENT 0x38
#define GDT_CODE_SEGMENT GDT_CODE64_SEGMENT
#define GDT_DATA_SEGMENT GDT_DATA64_SEGMENT
#define GDT_ENTRY_COUNT 9
#define GDT_ACC_KCODE 0x9A
#define GDT_ACC_KDATA 0x92
#define GDT_ACC_UCODE 0xFA
#define GDT_ACC_UDATA 0xF2
#define GDT_ACC_TSS 0x89
#define GDT_FLAGS_32BIT 0xC
#define GDT_FLAGS_64BIT 0xA
#define GDT_FLAGS_TSS  0x0

#pragma pack(push,1)
struct gdt_entry{
	uint16_t llow;
	uint16_t blow;
	uint8_t mlow;
	uint8_t access;
	uint8_t flhi;
	uint8_t bhigh;
}__attribute__((packed));
struct gdt_pointer{
	uint16_t limit;
	uint64_t gdtaddress;
}__attribute__((packed));
struct tss64{
	uint32_t reserved0;
	uint64_t rsp[3];
	uint64_t reserved1;
	uint64_t ist[7];
	uint64_t reserved2;
	uint16_t reserved3;
	uint16_t iomap_base;
}__attribute__((packed));
#pragma pack(pop)

extern struct gdt_entry entries[GDT_ENTRY_COUNT];
extern struct tss64 tss;

void gdt_set_normal_entry(struct gdt_entry *entry,uint32_t base,uint8_t flags,uint8_t access,uint32_t limit);
void gdt_set_system_entry(struct gdt_entry *entry_1,struct gdt_entry *entry_2,uint64_t base64,uint8_t flags,uint8_t access,uint32_t limit);
void gdt_set_kernel_stack(uint64_t rsp0);
void gdt_set_ist(int index,uint64_t stack_top);
void gdt_init(void);

#endif
