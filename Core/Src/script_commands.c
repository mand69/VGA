#include "stm32_ub_vga_screen.h"
#include <stdlib.h>

#define X_RESOLUTION 640-1
#define Y_RESOLUTION 480-1

// Error states
enum ERR_STATES{
    TASK_SUCCES = 0,
    ERR_OUT_OF_BOUNDS = 1,
};

// int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved) // fontsize:1 small, 2 big
// {

// }

/**
 * @brief  This function draws a line between 2 coördinates. 
 * 
 * @param x_1 X-pos coördinate 1
 * @param y_1 Y-pos coördinate 1
 * @param x_2 X-pos coördinate 2
 * @param y_2 Y-pos coördinate 2
 * @param color Color of the line
 * @param weight Thickness of the line
 * @param reserved 
 * @return int 
 */
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
    // Error handling
    if (x_1 < 0 ||
        y_1 < 0 ||
        x_2 < 0 ||
        y_2 < 0 ||
        x_1 > X_RESOLUTION ||
        y_1 > Y_RESOLUTION ||
        x_2 > X_RESOLUTION ||
        y_2 > Y_RESOLUTION)
        return ERR_OUT_OF_BOUNDS;

    // Calculates absolute distance between coördinates
    int dx = abs((int)x_2 - (int)x_1);
    int dy = abs((int)y_2 - (int)y_1);

    int sx = (x_1 < x_2) ? 1 : -1;
    int sy = (y_1 < y_2) ? 1 : -1;

    int err = dx - dy;


    // Calculating and setting pixels
    while (1)
    {
        // Teken de pixel rondom het huidige punt
        int offset = weight / 2;

        for (int i = -offset; i <= offset; i++)
        {
            for (int j = -offset; j <= offset; j++)
                UB_VGA_SetPixel(x_1 + i, y_1 + j, color);
        }

        // Line completed?
        if (x_1 == x_2 && y_1 == y_2)
            return TASK_SUCCES;

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



// int API_draw_bitmap(int x_lup, int y_lup, int bm_nr)
// {

// }



// int API_clearscreen(int color)
// {

// }


///////////////////////////////////////////////////////////////////////
/////////////////////////// BONUS COMMANDS ////////////////////////////
///////////////////////////////////////////////////////////////////////



// int API_wait(int msecs)
// {

// }



// int API_repeat_commands(int nr_previous_commands, int iterations, int reserved)
// {

// }



// int API_draw_circle(int x, int y, int radius, int color, int reserved)
// {

// }



// int API_draw_figure(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int reserved)
// {

// }



