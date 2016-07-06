#include "basicconsole.h"

NAMESPACE_BEGIN
void BasicConsole::move_cursor()
{
    uint16_t cursor = m_cursor.y * 80 + m_cursor.x;

    outb(0x3D4, 14);
    outb(0x3D5, cursor >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor);
}

void BasicConsole::scroll()
{
    uint8_t color = make_color(Color::LightGrey, Color::Black);

    if (m_cursor.y >= 25)
    {
        for (int i = 0 * 80; i < 24 * 80; i++)
        {
            m_vbuf[i] = m_vbuf[i + 80];
        }

        for (int i = 24 * 80; i < 25 * 80; i++)
        {
            m_vbuf[i].color = color;
            m_vbuf[i].data = 0x20;
        }

        m_cursor.y = 24;
    }
}

BasicConsole::BasicConsole()
{
    m_cursor.x = 0;
    m_cursor.y = 0;
    m_vbuf = reinterpret_cast<VideoMemory*>(0xB8000u);
}

void BasicConsole::putc(char ch, uint8_t color)
{
    switch (ch)
    {
    case '\n':
        m_cursor.x = 0;
        m_cursor.y++;
        break;
    case 0x08:
        if (m_cursor.x)
        {
            m_cursor.x--;
        }
        break;
    default:
        if (ch >= ' ')
        {
            m_vbuf[m_cursor.y * 80 + m_cursor.x].color = color;
            m_vbuf[m_cursor.y * 80 + m_cursor.x].data = ch;
            m_cursor.x++;
        }
        break;
    };

    if (m_cursor.x >= 80)
    {
        m_cursor.x = 0;
        m_cursor.y++;
    }
}

void BasicConsole::puts(char* msg, uint8_t color)
{
    while (msg)
    {
        putc(*msg, color);
        msg++;
    }
}

NAMESPACE_END