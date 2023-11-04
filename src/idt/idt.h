#pragma once

#include "../utils/utils.h"

#pragma pack(push, 1)
typedef struct {
    u16 offset_low;
    u16 segment_selector;
    u8 zeroes;
    u8 DPL_and_Gate_type;
    u16 offset_high;
} Gate_Desc;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u16 size;
    u32 address;
} IDT_Desc;
#pragma pack(pop)

void handler(unsigned char vector);

void init_idt();

void enable_interrupt(IDT_Desc* idt_desc);