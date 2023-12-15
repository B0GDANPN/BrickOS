#include "print.h"
#include "../utils/utils.h"


static short* careet_ptr = START_OF_DISPLAY;

void print_hex(unsigned int num) {
  char res_buffer[11];
  res_buffer[0] = '0';
  res_buffer[1] = 'x';
  for (char i = 2; i < 11; ++i) {
    char digit = num >> 28;
    if (digit < 10){
      res_buffer[i] = digit + '0';
    } else {
      res_buffer[i] = digit - 10 + 'A';
    }
    num <<= 4;
  }
  res_buffer[10] = '\0';
  print(res_buffer);
}

void print_dec(int num) {
  char res_buffer[12];
  char i = 0;
  if (num < 0){
    res_buffer[0] = '-';
    num = -num;
    i++;
  }
  char j = 0;
  char tmp[10];
  do {
    tmp[j++] = num % 10 + '0';
    num /= 10;
  } while (num > 0);
  for (int k = j - 1; k >= 0; --k){
    res_buffer[i++] = tmp[k];
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
    short* a = START_OF_DISPLAY + y * 80 + x;
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

void println(char* str) {
  print(str);
  new_line();
}

void print(char* str) {
  print_string(str, 0xf, &careet_ptr);
}

void vga_clear_screen(){
  memset(START_OF_DISPLAY, 0, 80 * 25 * 2);
  careet_ptr = START_OF_DISPLAY;
}

void shift_screen(){
  memcpy(START_OF_DISPLAY, START_OF_DISPLAY + 80, 80 * 24 * 2);
  memset(END_OF_DISPLAY - 80, 0, 80 * 2);
}

void vprint_format(char* str, va_list list) {
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
				print_dec(n);
			} else if (c == 's') {
				char* n = va_arg(list, char*);
				print(n);
			} else if (c == 'c') {
				char n = va_arg(list, char);
				print_char(n);
			} else if (c == 'x') {
				int n = va_arg(list, int);
				print_hex(n);
			}
			flag = 0;
		} else {
			print_char(c);
		}
		tmp++;
	}
}

void print_format(char* str, ...) {
	va_list list;
	va_start(list, str);
	vprint_format(str, list);
  va_end(list);
}

void display_console(u8* buffer);