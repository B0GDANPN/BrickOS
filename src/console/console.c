#include "../print/print.h"
#include "console.h"
#include "../alloc/alloc.h"


void init_console(Console* console, u32 width, u32 height, u32 padding_x, u32 padding_y){
    console->width = width;
    console->height = height;
    console->buffer = kernel_calloc(width * height, sizeof(u8));
    console->padding_x = padding_x;
    console->padding_y = padding_y;
    console->careet_x = 0;
    console->careet_y = 0;
}


void console_print_char_absolute(Console* console, u32 x, u32 y, u8 symbol){
    print_char_designed(symbol, COLOR_BLACK, x + console->padding_x, y + console->padding_y);
}

void console_print_char(Console *console, char symbol){
    if (symbol == '\n') {
        console_new_line(console);
    } else {
        // console_print_char_absolute(console, console->careet_x, console->careet_y, symbol);
        console->buffer[console->careet_y * console->width + console->careet_x] = symbol;
        console->careet_y += (console->careet_x + 1) / console->width;
        console->careet_x = (console->careet_x + 1) % console->width;
    }


    if (console->careet_y >= console->height){
        console_shift_screen(console);
        console->careet_x = 0;
        console->careet_y = console->height - 1;
    }
}

void console_print_string(Console *console, char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        console_print_char(console, str[i]);
    }
}

void console_new_line(Console *console){
    console->careet_x = 0;
    console->careet_y++;
}


void console_shift_screen(Console *console){
    memcpy(console->buffer, console->buffer + console->width, console->width * (console->height - 1) * sizeof(u8));
    memset(console->buffer + console->width * (console->height - 1), 0, console->width * sizeof(u8));
}

void console_display(Console* console){
    for (int y = 0; y < console->height; ++y){
        for (int x = 0; x < console->width; ++x){
            console_print_char_absolute(console, x, y, console->buffer[y * console->width + x]);
            // console_print_char_absolute(console, 0, 0, '@');
        }
    }
}