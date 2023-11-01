
#include "print/print.h"
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
  vga_clear_screen(); 
  for (int i = 0; i < sizeof(logo) / sizeof(logo[0]); i++) {
    println(logo[i]);
  }
  println("BrickOS");
  println("Version 1.0");
  println("Copyright (C) 2023");
  // print("@");
  // for (int i = 0; i < 100; ++i) {
  //   for (int j = 0; j < i; ++j)
  //     print(" ");
  //   print_int(i);
  //   println("");
  // }
  // for (int i = 0; i <18 ; ++i) {
  //     println("!");
  // }
  //vga_print_char('!', 0xf, 0, 17);
  // short* a = (short*)(0XB8000) + 17*80;
  // short printed_char = (color << 8) + symbol;
  // *a = printed_char;
  for (;;);
}
