// #define va_start(list) (void*) \
// list; \
// __asm{  \
//   mov list, esp \
// };
// #define va_arg(list, type) \
// (type)(list + sizeof(type)); \
// list = (void*)((type)list - sizeof(type));

// #define va_end(list) (list = (void)0);

#define START_OF_DISPLAY 0xB8000
#define END_OF_DISPLAY 0xB8FA0

#include "print.h"

short* careet_ptr;

void print_int(int num){
  if (num == 0){
    print("0");
    return;
  }

  char res_buffer[12];
  int i = 0;
  if (num < 0){
    res_buffer[0] = '-';
    num = -num;
    i++;
  }

  int j = 0;
  char tmp[10];
  while (num > 0){
    tmp[j] = (char)((num%10) + '0');
    num /= 10;
    j++;
  }
  for (int k = j - 1; k >= 0; k--){
    res_buffer[i] = tmp[k];
    i++;
  }
  res_buffer[i] = '\0';
  print(res_buffer);
}


void vga_print_char(char symbol, short color, int x, int y){
    short* a = (short*)(START_OF_DISPLAY) + y*80 + x;
    short printed_char = (color << 8) + symbol;
    *a = printed_char;
    
}

void vga_print_string(char* string, short color, short** start){
  short* a = *start;
  while (*string != '\0'){
    if (a >= (short*)END_OF_DISPLAY){
      shift_screen();
      a -= 80;
    }

    short printed_char = (color << 8) + *string;
    *a = printed_char;
    string++;
    a++;
  } 
  *start = a;
}

void println(char* str) {
  print(str);
  careet_ptr = (short*)START_OF_DISPLAY+((careet_ptr - (short*)START_OF_DISPLAY)/80 + 1)*80;
}

void print(char* str) {
    vga_print_string(str, 0xf, &careet_ptr);
}

void vga_clear_screen(){
  short* a = (short*)START_OF_DISPLAY;
  while (a < (short*)END_OF_DISPLAY){
    *a = 0;
    a++;
  }   
}

void init_printer(){
    vga_clear_screen();
    careet_ptr = (short*)START_OF_DISPLAY;
}
void shift_screen(){
  short* a = (short*)START_OF_DISPLAY;
  while (a < (short*)(END_OF_DISPLAY - 80)){
    *a = *(a + 80);
    a++;
  }
  for(short* b = (short*)(END_OF_DISPLAY) - 80; b < (short*)(END_OF_DISPLAY); b++){
    *b = 0;
  }
}

