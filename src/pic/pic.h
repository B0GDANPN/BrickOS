#pragma once

void init_pic();
void mask_irq();
void mask_timer();

void fill_registers();

void send_eoi(int is_from_slave);