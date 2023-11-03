

typedef void* va_list;

#define va_start(list, paramN) \
list = (char*)&paramN + sizeof(&paramN);

#define va_arg(list, type) \
*(type*)(list); \
list = (char*)(list + sizeof(type*));

#define va_end(list) (list = (void*)0)

#define START_OF_DISPLAY 0xB8000
#define END_OF_DISPLAY 0xB8FA0
#define COLOR_BLACK 0xf

#include "print.h"

short* careet_ptr = (short*)START_OF_DISPLAY;


void print_num(int num, int base){
  if (num == 0){
    print_char('0');
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
    int digit = num % base;
    if (digit < 10){
      tmp[j] = (char)(digit + '0');
    } else {
      tmp[j] = (char)(digit - 10 + 'a');
    }

    num /= base;
    j++;
  }
  for (int k = j - 1; k >= 0; k--){
    res_buffer[i] = tmp[k];
    i++;
  }
  res_buffer[i] = '\0';
  print(res_buffer);
}

void print_char(char symbol){
    short* a = careet_ptr;
    if (a >= (short*)END_OF_DISPLAY) {
      shift_screen();
      a -= 80;
    }
    short printed_char = (COLOR_BLACK << 8) + symbol;
    *a = printed_char;
    careet_ptr = a + 1;
}

void print_char_designed(char symbol, short color, int x, int y){
    short* a = (short*)(START_OF_DISPLAY) + y*80 + x;
    short printed_char = (color << 8) + symbol;
    *a = printed_char;
    
}

void print_string(char* string, short color, short** start){
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
void enter(){
  careet_ptr = (short*)START_OF_DISPLAY + ((careet_ptr - (short*)START_OF_DISPLAY) / 80 + 1) * 80;
}

void println(char* str) {
  print(str);
  enter();
}

void print(char* str) {
    print_string(str, 0xf, &careet_ptr);
}

void vga_clear_screen(){
  short* a = (short*)START_OF_DISPLAY;
  while (a < (short*)END_OF_DISPLAY){
    *a = 0;
    a++;
  }   
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
      enter();
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