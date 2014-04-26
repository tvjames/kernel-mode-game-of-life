/*
 * kernel.c
 * original: http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel
 */

#define _LINES 25
#define _COLS 80
#define _BYTESPERCHAR 2

#include "kernel.h"

void kmain(void) 
{
    char *str = "My first kernel yo! dont dskgsdkgsdjlgkjdgsjgdsljkgsdklgkljgsdjklsdgjgdsjglkslgksjlskgdjgjlsdksgdjlksgjkdlgsdljsgldjksgdlj";
    screen_write_char(0, 0, '@', White, Black);
    screen_write_char(0, 79, '@', White, Black);
    screen_write_char(24, 0, '@', White, Black);
    screen_write_char(24, 79, '@', White, Black);

    unsigned int i = 0;

    screen_clear();

    screen_write_string(2, 2, str, Blue, LightGrey);

    return;
}

void screen_write_char(unsigned int row, unsigned int col, char value, color_t foreground, color_t background)
{
    if (row >= _LINES) {
        screen_write_char(0, 0, '-', Red, White);
        return;
    }
    if (col >= _COLS) {
        screen_write_char(0, 0, '+', Red, White);
        return;
    }
    static char *vidptr = (char*)0xb8000;

    unsigned int position = (row * _COLS * _BYTESPERCHAR) + (col * _BYTESPERCHAR);
    unsigned char attributes = background << 8 | foreground;

    if (position >= (_LINES * _COLS * _BYTESPERCHAR)) {
        screen_write_char(0, 0, '=', Red, White);
        return;
    }

    vidptr[position] = value;
    vidptr[position + 1] = attributes;
}

void screen_write_string(unsigned int row, unsigned int col, char *value, color_t foreground, color_t background) 
{
    unsigned int position = 0;
    unsigned int length = strlen(value);
    for(int i = 0; i < length; i++) {
        if (col + position >= _COLS) {
            row++;
            position = 0;
        }
        screen_write_char(row, col + position++, value[i], foreground, background);
    }
}

void screen_clear() 
{
    unsigned int index = 0;
    while (index < _COLS * _LINES) {
        screen_write_char(index / _COLS, index % _COLS, '*', White, Black);
        index++;
    }
}




