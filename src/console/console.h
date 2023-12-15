#pragma once
#include "../utils/utils.h"

typedef struct {
    u8* buffer;
    u32 careet_x;
    u32 careet_y;
    u32 padding_x;
    u32 padding_y;
    u32 width;
    u32 height;

} Console;

// void init_console(Console* console, short* start_of_display, short width, short height, short left_offset, short right_offset);
void init_console(Console* console, u32 width, u32 height, u32 padding_left, u32 padding_right);

void console_display(Console* console);
void console_new_line(Console *console);
void console_shift_screen(Console *console);
void console_print_char(Console *console, char symbol);
void console_print_char_absolute(Console* console, u32 x, u32 y, u8 symbol);
void console_print_string(Console* console, char* str);

// void console_new_line(Console* console);
// void console_shift_screen(Console* console);
// void console_print_char_designed(Console* console, char symbol, short color);