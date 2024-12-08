#include "Display.h"
#include "ev3api.h"
Display::Display()
{
}

Display::~Display()
{
}
    
void Display::display(const char *str)
{
    count++;
    ev3_lcd_draw_string(str,10,10*count);
    if(count >= 12){
        count = 0;
    }
}

