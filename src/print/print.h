#pragma once

#include "../utils/utils.h"


#define START_OF_DISPLAY (short*)0xB8000
#define END_OF_DISPLAY (short*)0xB8FA0
#define COLOR_BLACK 0xf

void vga_clear_screen();

void print_char(char symbol);

void print_char_designed(char symbol, short color, int x, int y);

void print_string(char *string, short color, short **start);

void print(char *str);

void print_dec(int n);

void print_hex(unsigned int num);

void vprint_format(char *str, va_list);

void print_format(char *str, ...);

void println(char *str);

void new_line();

void shift_screen();
