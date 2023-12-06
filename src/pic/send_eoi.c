#include "../pic/pic.h"

void send_eoi(int is_from_slave){
  if (is_from_slave){
    __asm__ __volatile__ (
      // ".intel_syntax noprefix\n"
      // "mov %al, $0x20\n"
      // "out $0x20, %al\n"
      // "out $0xA0, %al\n");
      "mov $0x20, %al\n"
      "out %al, $0x20\n"
      "out %al, $0xA0\n");
  }
  else{
    __asm__ __volatile__(
      // ".intel_syntax noprefix\n"
      "mov $0x20, %al\n"
      "out %al, $0x20\n");
  }
}