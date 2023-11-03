#pragma once

typedef unsigned int size_t;

void vga_clear_screen();

void print_char(char symbol);

void print_char_designed(char symbol, short color, int x, int y);

void print_string(char *string, short color, short **start);

void print(char *str);

void print_num(int n, int base);

void print_format(char *str, ...);

void println(char *str);

void new_line();

void shift_screen();
