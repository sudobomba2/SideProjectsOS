#ifndef __SIDEPROJECTS_CMOS_UTILITY_H__
#define __SIDEPROJECTS_CMOS_UTILITY_H__
#pragma once

#include "asm.h"
#include "stdint.h"

#define CMOS_INDEX_PORT 0x70
#define CMOS_DATA_PORT 0x71
#define CMOS_NMI_BIT 0x40
#define NMI_ENABLE(data) ((data)|(CMOS_NMI_BIT))
#define NMI_DISABLE(data) ((data)&(~(CMOS_NMI_BIT)))
#define RTC_CURRENT_SEC 0x0
#define RTC_ALARM_SEC 0x1
#define RTC_CURRENT_MIN 0x2
#define RTC_ALARM_MIN 0x3
#define RTC_CURRENT_HOUR 0x4
#define RTC_ALARM_HOUR 0x5
#define RTC_DAY_OF_WEEK 0x6
#define RTC_DAY_OF_MONTH 0x7
#define RTC_MONTH 0x8
#define RTC_YEAR 0x9
#define STATUS_REG_A 0xA
#define STATUS_REG_A_UPDATE_IN_PROGRESS 0x80
#define STATUS_REG_B 0xB
#define STATUS_REG_C 0xC
#define STATUS_REG_D 0xD
#define CMOS_DIAGNOSTIC_STATUS 0xE
#define CMOS_DIAGNOSTIC_RTC_LOST_POWER 0x80
#define CMOS_SHUTDOWN_STATUS 0xF

static inline int cmos_select_ram(uint8_t index){outport_b(CMOS_INDEX_PORT,index);return 0;}
static inline uint8_t cmos_read_ram(void){return inport_b(CMOS_DATA_PORT);}
static inline int cmos_write_ram(uint8_t data){outport_b(CMOS_DATA_PORT,data);return 0;}
static inline uint8_t cmos_read(uint8_t registers){outport_b(CMOS_INDEX_PORT,registers&0x7F);return inport_b(CMOS_DATA_PORT);}
static inline void cmos_write(uint8_t registers,uint8_t value){outport_b(CMOS_INDEX_PORT,registers&0x7F);outport_b(CMOS_DATA_PORT,value);return;}
static inline uint8_t bcd_to_bin(uint8_t value){return (value&0x0F)+((value>>4)*10);}
int cmos_init(void);

#endif
