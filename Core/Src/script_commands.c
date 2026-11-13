#include "stm32_ub_vga_screen.h"
#include <stdlib.h>

#define X_MAX 320-1
#define Y_MAX 240-1

// Error states
enum ERR_STATES{
    TASK_SUCCES = 0,
    ERR_OUT_OF_BOUNDS = 1,
    ERR_INVALID_VALUE = 2
};

// int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved) // fontsize:1 small, 2 big
// {

// }


/**
 * @brief  This function draws a line on the screen.
 * 
 * @param x_1 X-pos coördinate of the first point
 * @param y_1 Y-pos coördinate of the first point
 * @param x_2 X-pos coördinate of the second point
 * @param y_2 Y-pos coördinate of the second point
 * @param color Color of the line
 * @param weight Thickness of the line
 * @param reserved Reserved parameter
 * @return int error
 */
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
    // Error handling
    if (x_1 < 0 ||
        y_1 < 0 ||
        x_2 < 0 ||
        y_2 < 0 ||
        x_1 > X_MAX ||
        y_1 > Y_MAX ||
        x_2 > X_MAX ||
        y_2 > Y_MAX)
        return ERR_OUT_OF_BOUNDS;
        
    if (color  < 0    ||
        color  > 0xFF ||
        weight < 0)
        return ERR_INVALID_VALUE;

    // Calculates absolute distance between coördinates
    int dx = abs((int)x_2 - (int)x_1);
    int dy = abs((int)y_2 - (int)y_1);

    int sx = (x_1 < x_2) ? 1 : -1;
    int sy = (y_1 < y_2) ? 1 : -1;

    int err = dx - dy;


    // Calculating and setting pixels
    while (1)
    {
        // Draw pixel and thickness
        int offset = weight / 2;

        for (int i = -offset; i <= offset; i++)
        {
            for (int j = -offset; j <= offset; j++)
            {
                // Check if pixels are within bounds
                if ((x_1 + i >= 0 && x_1 + i <= X_MAX) &&
                    (y_1 + j >= 0 && y_1 + j <= Y_MAX))
                    UB_VGA_SetPixel(x_1 + i, y_1 + j, color);
            }
        }

        // Line completed?
        if (x_1 == x_2 && y_1 == y_2)
            return TASK_SUCCES;

        // Bresenham's line algorithm
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


/**
 * @brief  This function draws a rectangle on the screen.
 *  * 
 * @param x X-pos coördinate of the top-left corner
 * @param y Y-pos coördinate of the top-left corner
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 * @param color Color of the rectangle
 * @param filled Fill status of the rectangle
 * @param reserved1 Reserved parameter
 * @param reserved2 Reserved parameter
 * @return int 
 */
int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int reserved1, int reserved2) // e.g.: weight, bordercolor
{
    // Error handling
    if (x           < 0     ||
        y           < 0     ||
        x + width   > X_MAX ||
        y + height  > Y_MAX)
        return ERR_OUT_OF_BOUNDS;


    // Check every pixel of the rectangle
    for (int yp = 0; yp < height; yp++)
    {
        for (int xp = 0; xp < width; xp++)
        {
            // Filled
            if (filled == 1)
                UB_VGA_SetPixel(x + xp, y + yp, (uint8_t)color);

            // Not filled
            else
            {
                if (xp == 0 || xp == width - 1 ||
                    yp == 0 || yp == height - 1)
                    UB_VGA_SetPixel(x + xp, y + yp, (uint8_t)color);
            }
        }
    }

    return 0;
}



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



