
#include "io.h"
#include "strings.h"
#include "screen.h"

#define _VIDEO_ADDRESS 0xb8000
#define _LINES 25
#define _COLS 80
#define _BYTESPERCHAR 2

void screen_write_box()
{
    screen_write_char(0, 0, '@', White, Black);
    screen_write_char(0, 79, '@', White, Black);
    screen_write_char(24, 0, '@', White, Black);
    screen_write_char(24, 79, '@', White, Black);

    // write debug
    // for (char i = 0; i < 20; i++) {
    //     screen_write_byte(0, 2 + (i * 3), i, Green, Black);
    //     screen_write_char_as_bitstring(1 + i, 2, i, Green, Black);
    // }
}

void screen_init()
{
    screen_clear(' ');

    screen_write_box();
    screen_write_string(0, 2, "Kernel mode Game of Life", Red, Black);
    screen_cursor_to(0, 33);
}

void screen_write_byte(unsigned int row, unsigned int col, char value, color_t foreground, color_t background)
{
    char l = (0x0F & value);
    if (l > 9) {
        l += 7;
    }
    char h = (0x0F & (value >> 4));
    if (h > 9) {
        h += 7;
    }
    screen_write_char(row, col+0, h+0x30, foreground, background);
    screen_write_char(row, col+1, l+0x30, foreground, background);

    screen_write_box();
}

void screen_write_word(unsigned int row, unsigned int col, unsigned int value, color_t foreground, color_t background)
{
    screen_write_byte(row, col+0, value >> 24, foreground, background);
    screen_write_byte(row, col+2, value >> 16, foreground, background);
    screen_write_byte(row, col+4, value >>  8, foreground, background);
    screen_write_byte(row, col+6, value >>  0, foreground, background);

    screen_write_box();
}

void screen_write_char_as_bitstring(unsigned int row, unsigned int col, char value, color_t foreground, color_t background)
{
    for (int i = 0; i < 8; i++) {
        char c = (value & (0x01 << (7-i))) ? '1' : '0';
        screen_write_char(row, col+i, c, foreground, background);
    }
    screen_write_char(row, col+8, 'b', foreground, background);

    screen_write_box();
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
    static char *vidptr = (char*)_VIDEO_ADDRESS;

    unsigned int position = (row * _COLS * _BYTESPERCHAR) + (col * _BYTESPERCHAR);
    unsigned char attributes = background << 4 | foreground;

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
    int length = strlen(value);
    for(int i = 0; i < length; i++) {
        if (col + position >= _COLS) {
            row++;
            position = 0;
        }
        screen_write_char(row, col + position++, value[i], foreground, background);
    }

    screen_write_box();
}

void screen_clear(char value) 
{
    unsigned int index = 0;
    while (index < _COLS * _LINES) {
        screen_write_char(index / _COLS, index % _COLS, value, White, Black);
        index++;
    }
}

// http://wiki.osdev.org/Text_Mode_Cursor
void screen_cursor_to(unsigned int row, unsigned int col)
{
    /* void update_cursor(int row, int col)
     * by Dark Fiber
     */
    unsigned short position = (row*_COLS) + col;

    // cursor LOW port to vga INDEX register
    port_byte_out(0x3D4, 0x0F);
    port_byte_out(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    port_byte_out(0x3D4, 0x0E);
    port_byte_out(0x3D5, (unsigned char )((position>>8)&0xFF));
}
