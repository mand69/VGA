#include "stm32_ub_vga_screen.h"
#include "font_5x7.h"
#include <stdlib.h>
#include <string.h>

#define X_MAX 320-1
#define Y_MAX 240-1

// Error states
enum ERR_STATES{
    TASK_SUCCES = 0,
    ERR_OUT_OF_BOUNDS = 1,
    ERR_INVALID_VALUE = 2
};

/**
 * @brief  This function draws text using the 5x7 bitmap font.
 *
 * @param x_lup Left position of the text
 * @param y_lup Top position of the text
 * @param color Text color
 * @param text Text to draw; lowercase is converted to uppercase
 * @param fontname Font name (currently "5x7")
 * @param fontsize 1 for normal size, 2 for double size
 * @param fontstyle Reserved; 0 for normal style
 * @param reserved Reserved parameter
 * @return int error
 */
int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname,
                  int fontsize, int fontstyle, int reserved)
{
    int character_spacing = 1 * fontsize;
    int text_length = strlen(text);

    if (x_lup < 0 ||
        y_lup < 0 ||
        x_lup + (text_length)*(FONT_5X7_WIDTH + character_spacing) - character_spacing - 1 > X_MAX ||
        y_lup + (FONT_5X7_HEIGHT - 1) > Y_MAX
    )
    return ERR_OUT_OF_BOUNDS;


    if (text == NULL ||
        fontname == NULL ||
        color < 0 ||
        color > 0xFF ||
        fontsize < 1 ||
        fontsize > 2 
        )
        return ERR_INVALID_VALUE;


    int cursor_x = x_lup;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            cursor_x += (FONT_5X7_WIDTH + character_spacing) * fontsize;
            continue;
        }

        int character_index;

        if (text[i] >= 'A' && text[i] <= 'Z')
            character_index = text[i] - 'A';
        else if (text[i] >= 'a' && text[i] <= 'z')
            character_index = text[i] - 'a';
        else if (text[i] >= '0' && text[i] <= '9')
            character_index = 26 + (text[i] - '0');
        else
            character_index = FONT_5X7_CHAR_COUNT - 1;

        for (int row = 0; row < FONT_5X7_HEIGHT; row++)
        {
            for (int column = 0; column < FONT_5X7_WIDTH; column++)
            {
                if (font_5x7[character_index][row] & (1 << (FONT_5X7_WIDTH - 1 - column)))
                {
                    for (int scale_y = 0; scale_y < fontsize; scale_y++)
                    {
                        for (int scale_x = 0; scale_x < fontsize; scale_x++)
                        {
                            int xp = cursor_x + (column * fontsize) + scale_x;
                            int yp = y_lup + (row * fontsize) + scale_y;

                            if (xp >= 0 && xp <= X_MAX &&
                                yp >= 0 && yp <= Y_MAX
                                )
                                UB_VGA_SetPixel(xp, yp, (uint8_t)color);
                        }
                    }
                }
            }
        }

        cursor_x += (FONT_5X7_WIDTH + character_spacing) * fontsize;
    }

    return TASK_SUCCES;
}


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
        y_2 > Y_MAX
        )
        return ERR_OUT_OF_BOUNDS;
        
    if (color  < 0    ||
        color  > 0xFF ||
        weight < 0
        )
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
                    (y_1 + j >= 0 && y_1 + j <= Y_MAX)
                    )
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
        y + height  > Y_MAX
        )
        return ERR_OUT_OF_BOUNDS;

    if (color  < 0      ||
        color  > 0xFF   ||
        filled < 0      ||
        filled > 1
        )
        return ERR_INVALID_VALUE;


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
                    yp == 0 || yp == height - 1
                    )
                    UB_VGA_SetPixel(x + xp, y + yp, (uint8_t)color);
            }
        }
    }

    return TASK_SUCCES;
}



// int API_draw_bitmap(int x_lup, int y_lup, int bm_nr)
// {

// }



/**
 * @brief  This function fills the screen with one color.
 *
 * @param color Color used to clear the screen
 * @return int error
 */
int API_clearscreen(int color)
{
    // Error handling
    if (color < 0 ||
        color > 0xFF
        )
        return ERR_INVALID_VALUE;

    UB_VGA_FillScreen((uint8_t)color);

    return TASK_SUCCES;
}


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



