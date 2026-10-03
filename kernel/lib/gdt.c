#include "gdt.h"

struct gdt_entry entries[GDT_ENTRY_COUNT] __attribute__((aligned(16)));
struct tss64 tss __attribute__((aligned(16)));

void gdt_set_normal_entry(struct gdt_entry *entry,uint32_t base,uint8_t flags,uint8_t access,uint32_t limit){
	entry->llow=limit&0xFFFF;
	entry->blow=base&0xFFFF;
	entry->mlow=(base>>16)&0xFF;
	entry->access=access;
	entry->flhi=((flags&0x0F)<<4)|((limit>>16)&0x0F);
	entry->bhigh=(base>>24)&0xFF;
	return;
}

void gdt_set_system_entry(struct gdt_entry *entry_1,struct gdt_entry *entry_2,uint64_t base64,uint8_t flags,uint8_t access,uint32_t limit){
	uint32_t base32=(uint32_t)base64;
	entry_1->llow=limit&0xFFFF;
	entry_1->blow=base32&0xFFFF;
	entry_1->mlow=(base32>>16)&0xFF;
	entry_1->access=access;
	entry_1->flhi=((flags&0x0F)<<4)|((limit>>16)&0x0F);
	entry_1->bhigh=(base32>>24)&0xFF;
	if(entry_2){
		uint32_t hi=(uint32_t)(base64>>32);
		entry_2->llow=hi&0xFFFF;
		entry_2->blow=(hi>>16)&0xFFFF;
		entry_2->mlow=0;
		entry_2->access=0;
		entry_2->flhi=0;
		entry_2->bhigh=0;
	}
	return;
}

void gdt_set_kernel_stack(uint64_t rsp0){tss.rsp[0]=rsp0;return;}
void gdt_set_ist(int index,uint64_t stack_top){if(index>=1&&index<=7)tss.ist[index-1]=stack_top;return;}

void gdt_init(void){
	gdt_set_normal_entry(&entries[0],0,0x0,0x00,0x00000);
	gdt_set_normal_entry(&entries[1],0,GDT_FLAGS_32BIT,GDT_ACC_KCODE,0xFFFFF);
	gdt_set_normal_entry(&entries[2],0,GDT_FLAGS_32BIT,GDT_ACC_KDATA,0xFFFFF);
	gdt_set_normal_entry(&entries[3],0,GDT_FLAGS_64BIT,GDT_ACC_KCODE,0xFFFFF);
	gdt_set_normal_entry(&entries[4],0,GDT_FLAGS_32BIT,GDT_ACC_KDATA,0xFFFFF);
	gdt_set_normal_entry(&entries[5],0,GDT_FLAGS_32BIT,GDT_ACC_UDATA,0xFFFFF);
	gdt_set_normal_entry(&entries[6],0,GDT_FLAGS_64BIT,GDT_ACC_UCODE,0xFFFFF);
	tss.iomap_base=sizeof(tss);
	gdt_set_system_entry(&entries[7],&entries[8],(uint64_t)(uintptr_t)&tss,GDT_FLAGS_TSS,GDT_ACC_TSS,sizeof(tss)-1);
	struct gdt_pointer gdtp={sizeof(entries)-1,(uint64_t)(uintptr_t)&entries};
	__asm__ volatile("lgdt %0"::"m"(gdtp));
	__asm__ volatile(
		"pushq $%c[cs]\n\t"
		"leaq 1f(%%rip),%%rax\n\t"
		"pushq %%rax\n\t"
		"lretq\n"
		"1:\n\t"
		"movw $%c[ds],%%ax\n\t"
		"movw %%ax,%%ds\n\t"
		"movw %%ax,%%es\n\t"
		"movw %%ax,%%ss\n\t"
		"xorl %%eax,%%eax\n\t"
		"movw %%ax,%%fs\n\t"
		"movw %%ax,%%gs\n\t"
		:
		:[cs]"i"(GDT_CODE64_SEGMENT),[ds]"i"(GDT_DATA64_SEGMENT)
		:"rax","memory");

	__asm__ volatile("ltr %w0"::"r"((uint16_t)GDT_TSS_SEGMENT));
	return;
}
