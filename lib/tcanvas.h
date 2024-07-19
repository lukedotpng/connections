#ifndef TCANVAS_H
#define TCANVAS_H

#include <stdio.h>
#include "connections.h"

enum color {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    DEFAULT,
    RESET,
};


/**
 * @brief  
 * Add n amount of new lines to create 
 * @param height  
 * @return int 
 */
int initialize_canvas(int height);

void draw(const char* string, enum color text_color, enum color background_color);

/**
 * @brief Draws the connection board
 * 
 * @param board 
 */
void tdraw_board(const cboard board);
/**
 * @brief Draws a connection tile
 * 
 * @param item 
 * @param length 
 * @param height 
 * @param column
 * @param row
 */
void tdraw_tile(const gitem item, int length, int height, int column_index, int row_index);

void tdraw_tile_padding(int tile_length);

void tdraw_guessed_row(const cgroup group);

const char* color_to_ansi_text(enum color color);
const char* color_to_ansi_background(enum color color);

#endif