#include "idt.h"
#include "../tramplins/tramplins.h"
#include "../alloc/alloc.h"
#include "../print/print.h"

#define IDT_SIZE 256


void init_idt() {
    Gate_Desc* idt = kernel_malloc(IDT_SIZE * sizeof(Gate_Desc));
    null_check(idt);

    u32 tramplins[IDT_SIZE];
    init_tramplins_array(tramplins);

    for (int vector = 0; vector < IDT_SIZE; ++vector) {
        u32 tramplin_i = tramplins[vector];
        u16 low_16_bits = tramplin_i & 0xFFFF; // gets the low 16 bits of hadler
        u16 high_16_bits = tramplin_i >> 16;   // gets the high 16 bits of hadler

        u16 segment_selector;
        asm(
            "mov %%cs, %0"
            : "=r"(segment_selector)
            : "r"(segment_selector)
            :
        );

        Gate_Desc desc = (Gate_Desc){
            .offset_high = high_16_bits,
            .DPL_and_Gate_type = 0b10001111, // or 0b10001110
            .zeroes = 0,
            .segment_selector = segment_selector,
            .offset_low = low_16_bits
        };
        idt[vector] = desc;
    }

    IDT_Desc IDT_Descriptor = (IDT_Desc){
        .address = (u32)idt,
        .size = (u16)(IDT_SIZE * sizeof(Gate_Desc) - 1)
    };

    asm ( "lidt %0" : : "m"(IDT_Descriptor) );
}
