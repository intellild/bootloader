#include "kernel.h"

NAMESPACE_BEGIN
class BasicConsole
{
public:
    enum class Color : uint8_t
    {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGrey = 7,
        DarkGrey = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        LightBrown = 14,
        White = 15
    };

#pragma pack(push, 1)
    struct Cursor
    {
        uint8_t x;
        uint8_t y;
    };

    struct VideoMemory
    {
        uint8_t data;
        uint8_t color;
    };
#pragma pack(pop)

private:
    Cursor m_cursor;
    VideoMemory* m_vbuf;

private:
    void move_cursor();
    void scroll();

public:
    static constexpr uint8_t make_color(Color fore, Color back)
    {
        return static_cast<uint8_t>(fore) | (static_cast<uint8_t>(back) << 4);
    }

    BasicConsole();
    void putc(char ch, uint8_t color = make_color(Color::LightGrey, Color::Black));
    void puts(char* msg, uint8_t color = make_color(Color::LightGrey, Color::Black));
    void clear();
};
NAMESPACE_END