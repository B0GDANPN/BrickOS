#pragma once

void handler(unsigned char vector);

void init_idt();

void enable_interrupt(unsigned int idt_desc);
//void enable_interrupt();
