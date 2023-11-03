#include "idt.h"

void init_idt() {
    Gate_Desc desc = {

    }
    table = alloc();
    for (int i = 0; i< n; ++i){
        table[i] = &traplin_i;
    }
    Gate_Desc.ptr = &table
}

void enable_interrapt() {
    asm("lidt [&Gate_Desc]")
}