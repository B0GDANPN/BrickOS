#define ASSERTS_ON

#include "print/print.h"
#include "idt/idt.h"
#include "alloc/alloc.h"
#include "asserts/assert.h"
#include "print/print_logo.h"
#include "pic/pic.h"


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
  //kernel_panic("%x\n%d\n", 0xFE987514, 789654123);
  //char* str = "hello from panic";
  //kernel_assert(0, str)
  //kernel_panic("Panic!");
  for (;;);
}

