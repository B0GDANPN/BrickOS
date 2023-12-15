#define ASSERTS_ON

#include "print/print.h"
#include "idt/idt.h"
#include "alloc/alloc.h"
#include "asserts/assert.h"
#include "print/print_logo.h"
#include "pic/pic.h"
#include "console/console.h"
#include "context/context.h"



void kernel_entry()
{
  init_alloc();
  vga_clear_screen();
  init_idt();
  init_pic();



  init_consoles();
  init_contexts();


  // mask_irq();
  // mask_timer();
  //  print_logo();
  asm ("sti");
  // process_method();
  


  for (;;);
}

