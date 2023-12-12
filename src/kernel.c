#define ASSERTS_ON

#include "print/print.h"
#include "idt/idt.h"
#include "alloc/alloc.h"
#include "asserts/assert.h"
#include "print/print_logo.h"
#include "pic/pic.h"

void delay();

void kernel_entry() {
  init_alloc();
  vga_clear_screen(); 
  init_idt();
  init_pic();
  //mask_irq();
  //mask_timer();
  // print_logo();
  //print_format("%x\n%d\n", 0xFE987514, 789654123);
  asm ( "sti" : :);
  fill_registers();
  asm ("int $0x50");
  for (int i = 0; 1; ++i) {
    // delay();
    print_format("%d\n", i);
  //for (;;);
  }
}

void delay() {
  for (int j = 0; j < 1000000; ++j) {
    int a = j * j;
    int b = a;
  } 
}

