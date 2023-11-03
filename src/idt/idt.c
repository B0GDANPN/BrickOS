#include "idt.h"
#include "tramplines.h"
#include "../alloc/alloc.h"
#include "../print/print.h"

#define IDT_SIZE 256

#pragma pack(push, 1)
typedef struct {
    u16 offset_high;
    u8 DPL_and_Gate_type;
    u8 zeroes;
    u16 segment_selector;
    u16 offset_low;
} Gate_Desc;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    u16 size;
    u32 address;
} IDT_Desc;
#pragma pack(pop)

void handler(unsigned char vector) {
    println("PANIC!!!");
    asm(
        "cli\n\t"
        :
        :
    );
    for(;;);
   // print_format("%x", vector);
}

static IDT_Desc* IDT_Descriptor;

void init_idt() {
    Gate_Desc* idt = kernel_malloc(IDT_SIZE * sizeof(Gate_Desc));
    println("malloc!!!");
    null_check(idt);
    println("null check succesfull");
    for (int vector = 0; vector < IDT_SIZE; vector++) {

        void* handler = tramplin_0;
        //print_format();
        print_format("%d: %x\n", vector, (u32)handler);
        u16 low_16_bits = (u16)(((u32)handler << 16) >> 16); //gets the low 16 bits of hadler
        u16 high_16_bits = (u16)(((u32)handler) >> 16); //gets the high 16 bits of hadler

        u16 segment_selector;
        //print_format("%x", (u32)&init_idt);
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
        //print_format("%x\n", (u32)(&desc));
        idt[vector] = desc;
    }
    println("IDT table created!");
    IDT_Descriptor = (IDT_Desc*)kernel_malloc(sizeof(IDT_Desc));
    null_check(IDT_Descriptor);
    *IDT_Descriptor = (IDT_Desc){
        .address = (u32)idt,
        .size = (u16)(IDT_SIZE * sizeof(Gate_Desc) - 1)
    };
    // print_format("%x\n", (u32)IDT_Descriptor);
    // print_format("%d\n", (u16)(IDT_SIZE * sizeof(Gate_Desc) - 1));
    enable_interrupt((u32)IDT_Descriptor);
}

void enable_interrupt(unsigned int idt_desc) {
    u32 tmp = *(u32*)idt_desc;
     asm ( "lidt %0" : : "m"(tmp) );
     asm ( "sti" : : "m"(idt_desc) );
}