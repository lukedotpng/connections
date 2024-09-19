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

#define MIN_TILE_LENGTH 12



void initialize_canvas();

void exit_canvas();

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
 * @param row
 * @param board_placement
 */
void tdraw_tile(citem item, int length, int row, int board_placement);

void tdraw_padding(int length, int column, int row);

void tdraw_highlight_box(int tile_length, int left_padding_size, int column, int row);

void tdraw_guessed_row(cgroup group, int row, int length);

#endif