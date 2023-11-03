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