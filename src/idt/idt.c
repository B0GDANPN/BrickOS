#include "idt.h"
#include "tramplines.h"
#include "../alloc/alloc.h"
#include "../print/print.h"

#define IDT_SIZE 256

void handler(unsigned char vector) {
    println("PANIC!!!");
    asm(
        "cli\n\t"
        :
        :
    );
    for(;;);
}

void init_idt() {
    Gate_Desc* idt = kernel_malloc(IDT_SIZE * sizeof(Gate_Desc));
    null_check(idt);
    for (int vector = 0; vector < IDT_SIZE; vector++) {

        void* handler = tramplin_0;
        print_format("%d: %x\n", vector, (u32)handler);
        u16 low_16_bits = (u16)(((u32)handler << 16) >> 16); //gets the low 16 bits of hadler
        u16 high_16_bits = (u16)(((u32)handler) >> 16);      //gets the high 16 bits of hadler

        u16 segment_selector;
        asm(
            "mov %%ss, %0"
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
    IDT_Desc* IDT_Descriptor = (IDT_Desc*)kernel_malloc(sizeof(IDT_Desc));
    null_check(IDT_Descriptor);
    *IDT_Descriptor = (IDT_Desc){
        .address = (u32)idt,
        .size = (u16)(IDT_SIZE * sizeof(Gate_Desc) - 1)
    };

    enable_interrupt(IDT_Descriptor);
}

void enable_interrupt(IDT_Desc* idt_desc) {
     asm ( "lidt %0" : : "m"(*idt_desc) );
     asm ( "sti" : : "m"(idt_desc) );
}