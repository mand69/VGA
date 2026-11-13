#include "main.h"

// extern int API_draw_text(int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved); // fontsize:1 small, 2 big
extern int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);
extern int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int reserved1, int reserved2); // e.g.: weight, bordercolor
// extern int API_draw_bitmap(int x_lup, int y_lup, int bm_nr); 
// extern int API_clearscreen(int color);


// extern int API_wait(int msecs);
// extern int API_repeat_commands(int nr_previous_commands, int iterations, int reserved);  
 
// extern int API_draw_circle(int x, int y, int radius, int color, int reserved);
// extern int API_draw_figure(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int reserved);
