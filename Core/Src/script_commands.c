#include "stm32_ub_vga_screen.h"


int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved) // fontsize:1 small, 2 big
{

}


int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
    int dx = abs((int)x_2 - (int)x_1);
    int dy = abs((int)y_2 - (int)y_1);

    int sx = (x_1 < x_2) ? 1 : -1;
    int sy = (y_1 < y_2) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        // Teken de pixel(s) rondom het huidige punt
        int offset = weight / 2;

        for (int i = -offset; i <= offset; i++)
        {
            for (int j = -offset; j <= offset; j++)
            {
                UB_VGA_SetPixel(x_1 + i, y_1 + j, color);
            }
        }

        // Eindpunt bereikt?
        if (x_1 == x_2 && y_1 == y_2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x_1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y_1 += sy;
        }
    }
}



// int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int reserved, int reserved) // e.g.: weight, bordercolor
// {

// }



int API_draw_bitmap(int x_lup, int y_lup, int bm_nr)
{

}



int API_clearscreen(int color)
{

}


///////////////////////////////////////////////////////////////////////
/////////////////////////// BONUS COMMANDS ////////////////////////////
///////////////////////////////////////////////////////////////////////



int API_wait(int msecs)
{

}



int API_repeat_commands(int nr_previous_commands, int iterations, int reserved)
{

}



int API_draw_circle(int x, int y, int radius, int color, int reserved)
{

}



int API_draw_figure(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int reserved)
{

}



