#include "Display.h"
#include "ev3api.h"
Display::Display()
{
}

Display::~Display()
{
}

void Display::display(const char *str, int32_t x, int32_t y)
{
    ev3_lcd_draw_string (str, x, y);
}
    
