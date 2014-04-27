
typedef enum {
    Black        = 0x0,
    Blue         = 0x1,
    Green        = 0x2, 
    Cyan         = 0x3,
    Red          = 0x4,
    Magenta      = 0x5, 
    Brown        = 0x6,
    LightGrey    = 0x7,
    DarkGrey     = 0x8,
    LightBlue    = 0x9,
    LightGreen   = 0xA,
    LightCyan    = 0xB,
    LightRed     = 0xC,
    LightMagenta = 0xD,
    LightBrown   = 0xE,
    White        = 0xF
} color_t;


void screen_init();
void screen_clear(char value);
void screen_write_string(unsigned int row, unsigned int col, char *value, color_t foreground, color_t background);
void screen_write_char(unsigned int row, unsigned int col, char value, color_t foreground, color_t background);
void screen_write_char_as_bitstring(unsigned int row, unsigned int col, char value, color_t foreground, color_t background);
void screen_write_byte(unsigned int row, unsigned int col, char value, color_t foreground, color_t background);
void screen_write_word(unsigned int row, unsigned int col, unsigned int word, color_t foreground, color_t background);
void screen_cursor_to(unsigned int row, unsigned int col);
