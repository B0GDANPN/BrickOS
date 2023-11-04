
#include "print/print.h"
#include "idt/idt.h"
#include "alloc/alloc.h"

char* logo[] = {
  " .-----------. .--------------. .-----------. .--------------. .--------------.",
  "|  ______    | |  _______     | |   _____   | |     ______   | |  ___  ____   |",
  "| |_   _ \\   | | |_   __ \\    | |  |_   _|  | |   .' ___  |  | | |_  ||_  _|  |",
  "|   | |_) |  | |   | |__) |   | |    | |    | |  / .'   \\_|  | |   | |_/ /    |",
  "|   |  __ \\  | |   |  __ /    | |    | |    | |  | |         | |   |  __'.    |",
  "|  _| |__) | | |  _| |  \\ \\_  | |   _| |_   | |  \\ `.___.'\\  | |  _| |  \\ \\_  |",
  "| |_______/  | | |____| |___| | |  |_____|  | |   `._____.'  | | |____||____| |",
  "|            | |              | |           | |              | |              |",
  "\\-----------/ \\--------------/ \\-----------/ \\--------------/ \\--------------/",
  "\\.---------------.                                .-----------------------./",
  "                  \\.-------------. .------------./",
  "                   |     ___     | |    _____   |",
  "                   |   .'   '.   | |  /  __  |  |",
  "                   |  /  / \\  \\  | |  | (_ \\_|  |",
  "                   |  | |   | |  | |  '.__`-.   |",
  "                   |  \\  \\_/  /  | |   ____) |  |",
  "                   |   `.___.'   | |  \\_____.'  |",
  "                   |             | |            |",
  "                    \\-----------/   \\----------/",
};

void kernel_entry() {
  init_alloc();
  vga_clear_screen(); 
  // for (int i = 0; i < sizeof(logo) / sizeof(logo[0]); i++) {
  //   println(logo[i]);
  // }
  // println("BrickOS");
  // println("Version 1.0");
  // println("Copyright (C) 2023");

  // print_num(15, 16);
  // println("Start init idt");
  init_idt();
  // println("End init idt");
  // int a = 2*2-4;
  // int b = 1/a;
  // print_format("%d\n", b);
  for (;;);
}
