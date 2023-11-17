#include "utils.h"
#include "../print/print.h"

void null_check(void* ptr) {
	if (ptr == NULL) {
		println("Out of memory!");
      for(;;);
	}
}

void memcpy(void *dest, const void *src, size_t size)
{
  char* dest_char = (char*)dest;
  char* src_char = (char*)src;
  for (char* ptr = src_char; ptr < src_char + size; ++ptr){
    *(dest_char++) = *(char*)ptr;
  }
}

void memset(void *dest, char ch, size_t count)
{
  char* dest_char = (char*)dest;
  for (char* ptr = dest_char; ptr < dest_char + count; ++ptr){
    *ptr = ch;
  }
}

void vkernel_panic(char* str, va_list args) {
  asm ( "cli" : :);
  vga_clear_screen();
  vprint_format(str, args);
  for(;;);
}

void kernel_panic(char* str, ...) {
  va_list args;
  va_start(args, str);
  vkernel_panic(str, args);
  va_end(args);
}

void send_eoi(int flag){
  if (flag){
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