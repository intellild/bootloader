#include "print.h"
#include "common.h"

static uint16_t* video_memory;

static uint8_t cursor_x;
static uint8_t cursor_y;

void monitor_init()
{
    video_memory = (uint16_t*)0xB8000;
    cursor_x = 0;
    cursor_y = 0;
    monitor_clear();
}

static void move_cursor(void)
{
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
}

static void scroll(void)
{
    // Get a space character with the default colour attributes.
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    if (cursor_y >= 25)
    {
        int i;
        for (i = 0 * 80; i < 24 * 80; i++)
        {
            video_memory[i] = video_memory[i + 80];
        }

        for (i = 24 * 80; i < 25 * 80; i++)
        {
            video_memory[i] = blank;
        }

        cursor_y = 24;
    }
}

void monitor_put(char c)
{
    uint8_t backColour = 0;
    uint8_t foreColour = 7;
    uint8_t attributeByte = (backColour << 4) | (foreColour & 0x0F);
    uint16_t attribute = attributeByte << 8;
    uint16_t* location;

    switch (c)
    {
    case 0x08:
        if (cursor_x)
        {
            cursor_x--;
        }
        break;
    case 0x09:
        cursor_x = (cursor_x + 8) & ~(4 - 1);
        break;
    case '\r':
        cursor_x = 0;
        break;
    case '\n':
        cursor_x = 0;
        cursor_y++;
        break;
    default:
        if (c >= ' ')
        {
            location = video_memory + (cursor_y * 80 + cursor_x);
            *location = c | attribute;
            cursor_x++;
        }
        break;
    }

    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();

    move_cursor();
}

void monitor_clear(void)
{
    // Make an attribute byte for the default colours
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80 * 25; i++)
    {
        video_memory[i] = blank;
    }

    // Move the hardware cursor back to the start.
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void monitor_write(char* c)
{
    int i = 0;
    while (c[i])
    {
        monitor_put(c[i++]);
    }
}

void monitor_print_hex(uint64_t x, uint8_t bits)
{
    char hex[2 + (bits >> 2) + 1];
    char chtable[16] = "0123456789ABCDEF";
    int i;
    hex[0] = '0';
    hex[1] = 'x';
    hex[2 + (bits >> 2)] = '\0';

    for (i = 0; i < (bits >> 2); i++)
    {
        int tmp = (x >> (4 * i)) & 0xf;
        hex[(bits >> 2) + 1 - i] = chtable[tmp];
    }
    monitor_write(hex);
}
