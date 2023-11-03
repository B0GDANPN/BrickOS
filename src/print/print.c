typedef void* va_list;

#define va_start(list, paramN) \
list = (char*)&(paramN) + sizeof(&(paramN));

#define va_arg(list, type) \
*(type*)(list); \
list = (char*)((list) + sizeof(type*));

#define va_end(list) ((list) = (void*)0)

#define START_OF_DISPLAY (short*)0xB8000
#define END_OF_DISPLAY (short*)0xB8FA0
#define COLOR_BLACK 0xf

#include "print.h"

static short* careet_ptr = START_OF_DISPLAY;


void print_num(int num, int base){
  char res_buffer[12];
  int i = 0;
  if (num < 0){
    res_buffer[0] = '-';
    num = -num;
    i++;
  }

  int j = 0;
  char tmp[10];
  do{ // TODO: use do while cycle
    int digit = num % base;
    if (digit < 10){
      tmp[j] = (char)(digit + '0');
    } else {
      tmp[j] = (char)(digit - 10 + 'a');
    }

    num /= base;
    j++;
  } while (num > 0);
  for (int k = j - 1; k >= 0; k--){
    res_buffer[i] = tmp[k];
    i++;
  }
  res_buffer[i] = '\0';
  print(res_buffer);
}

void print_char(char symbol){
    short* a = careet_ptr;
    if (a >= END_OF_DISPLAY) {
      shift_screen();
      a -= 80;
    }
    short printed_char = (COLOR_BLACK << 8) + symbol;
    *a = printed_char;
    careet_ptr = a + 1;
}

void print_char_designed(char symbol, short color, int x, int y){
    short* a = START_OF_DISPLAY + y*80 + x;
    short printed_char = (color << 8) + symbol;
    *a = printed_char;
    
}

void print_string(char* string, short color, short** start){
  short* a = *start;
  while (*string != '\0'){
    if (a >= END_OF_DISPLAY){
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
void new_line(){
  careet_ptr = START_OF_DISPLAY + ((careet_ptr - START_OF_DISPLAY) / 80 + 1) * 80;
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

void println(char* str) {
  print(str);
  new_line();
}

void print(char* str) {
    print_string(str, 0xf, &careet_ptr);
}

void vga_clear_screen(){
  // while (a < END_OF_DISPLAY){ // TODO: do like memcpy and memzero
  //   *a = 0;
  //   a++;
  // }   
  memset(START_OF_DISPLAY, 0, 80 * 25 * 2);
}

void shift_screen(){
  // while (a < (END_OF_DISPLAY - 80)){
  //   *a = *(a + 80);
  //   a++;
  // }
  memcpy(START_OF_DISPLAY, START_OF_DISPLAY + 80, 80 * 24 * 2);
  // for(short* b = END_OF_DISPLAY - 80; b < END_OF_DISPLAY; ++b){
  //   *b = 0;
  // }
  
  memset(END_OF_DISPLAY - 80, 0, 80 * 2);
}

void print_format(char* str, ...) {
	va_list list;
	va_start(list, str);
	char* tmp = str;
	char flag = 0;
	while (1) {
		char c = *tmp;
		if (!c) {
			break;
		}
    if (c == '\n') {
      new_line();
    } else if (c == '%') {
			flag = 1;
		} else if (flag) {
			if (c == 'd') {
				int n = va_arg(list, int);
				print_num(n, 10);
			} else if (c == 's') {
				char* n = va_arg(list, char*);
				print(n);
			} else if (c == 'c') {
				char n = va_arg(list, char);
				print_char(n);
			} else if (c == 'x') {
				int n = va_arg(list, int);
				print_num(n, 16);
			}
			flag = 0;
		} else {
			print_char(c);
		}
		tmp++;
	}
}