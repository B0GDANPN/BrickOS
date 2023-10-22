#pragma once

void vga_clear_screen();
void vga_print_char(char symbol, short color, int x, int y);
void vga_print_string(char* string, short color, short** start);
void print(char* str);
void print_int(int n);
void println(char* str);
void shift_screen();
