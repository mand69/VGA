#include "main.h"

enum Color {
    black           = 0, 
    blue            = 1, 
    light_blue      = 2, 
    green           = 3, 
    light_green     = 4, 
    cyan            = 5, 
    light_cyan      = 6, 
    red             = 7, 
    light_red       = 8, 
    magenta         = 9, 
    light_magenta   = 10, 
    brown           = 11, 
    yellow          = 12, 
    gray            = 13, 
    white           = 14
}

void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color, uint8_t thickness)
{

}


void rectangle(uint16_t x_lup, uint16_t y_lup, uint16_t x_distance, uint16_t y_distance, uint8_t color, uint8_t filled)
{

}


void text(uint16_t nr, uint16_t x_lup, uint16_t y_lup, uint16_t text, uint8_t font, uint8_t font_size, uint8_t font_style)
{

}


void bitmap(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color, uint8_t thickness)
{

}


void clearscreen(uint16_t color)
{

}


///////////////////////////////////////////////////////////////////////
/////////////////////////// BONUS COMMANDS ////////////////////////////
///////////////////////////////////////////////////////////////////////

void wait(uint16_t msec)
{

}


void repeat(uint16_t amount, uint16_t repeats)
{

}


void circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color)
{

}


void figure(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t x4, uint16_t y4, uint16_t x5, uint16_t y5, uint8_t color)
{

}