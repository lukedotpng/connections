#ifndef TCANVAS_H
#define TCANVAS_H

#include <stdio.h>
#include "connections.h"

#define YELLOW_SOLVED_COLOR_PAIR   1
#define GREEN_SOLVED_COLOR_PAIR    2
#define BLUE_SOLVED_COLOR_PAIR     3
#define PURPLE_SOLVED_COLOR_PAIR   4
#define TILE_COLOR_PAIR            5
#define HIGHLIGHTED_COLOR_PAIR     6
#define SELECTED_COLOR_PAIR        7

void initialize_canvas();

/**
 * @brief Draws the connection board
 * 
 * @param board 
 */
void tdraw_board(cboard* board);
/**
 * @brief Draws a connection tile
 * 
 * @param item 
 * @param length 
 * @param height 
 * @param column
 * @param row
 */
void tdraw_tile(const citem item, int length, int height, int column_index, int row_index);

void tdraw_tile_padding(int tile_length, int column, int row);

void tdraw_highlight_box(int tile_length, int left_padding_size, int column, int row);

void tdraw_guessed_row(const cgroup group);

#endif