#include "../lib/tcanvas.h"
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void initialize_canvas() {
    // SCREEN* game_screen = newterm("Connections", NULL, NULL);
    initscr();

    // Setup color management
    start_color();
    use_default_colors();
    init_pair(TILE_COLOR_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(HIGHLIGHTED_COLOR_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(SELECTED_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(PURPLE_SOLVED_COLOR_PAIR, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(BLUE_SOLVED_COLOR_PAIR, COLOR_BLACK, COLOR_BLUE);
    init_pair(GREEN_SOLVED_COLOR_PAIR, COLOR_BLACK, COLOR_GREEN);
    init_pair(YELLOW_SOLVED_COLOR_PAIR, COLOR_BLACK, COLOR_YELLOW);

    cbreak(); 
    curs_set(0);
    noecho();
}

void tdraw_board(cboard* board) {
    // Finding longest clue length to determine the size of all tiles
    // using unsigned here isnt really needed, but extra safety since strlen returns unsigned
    unsigned int longest_item_length = 0;
    for(int i = 0; i < 16; i++) {
        if(strlen(board->items[i].clue) > longest_item_length) {
            longest_item_length = strlen(board->items[i].clue);
        }
    }
    // Add extra padding to the tile size
    int tile_length = longest_item_length + 2;
    int tile_height = 3;

    int item_count = 0;
    for(int row = 0; row < 4; row++) {
        // Draw blamk above
        for(int col = 0; col < 4; col++) {
            tdraw_tile(board->items[item_count], tile_length, tile_height, col, row);
            item_count++;
        }
    }
    // printf("\n");
}

void tdraw_tile(const citem item, int length, int height, int column_index, int row_index) {
    int clue_length = strlen(item.clue);
    int clue_padding = length - clue_length;

    // Some magic numbers dont mind these :P
    int column = column_index * (length + 2);
    int row = row_index * 4;

    int left_padding_size = clue_padding / 2;
    int right_padding_size = clue_padding - left_padding_size;


    if(item.is_selected) {
        attron(COLOR_PAIR(SELECTED_COLOR_PAIR));
    } else {
        attron(COLOR_PAIR(TILE_COLOR_PAIR));
    }

    // Upper padding
    tdraw_tile_padding(length, column, row);
    // Left padding
    tdraw_tile_padding(left_padding_size, column, row + 1);
    // Right padding
    tdraw_tile_padding(right_padding_size, column + (length - right_padding_size), row + 1);
    // Lower padding
    tdraw_tile_padding(length, column, row + 2);
    
    // Clue
    if(item.is_highlighted) {
        attron(A_UNDERLINE | A_BOLD);
    }
    mvprintw(row + 1, column + left_padding_size, item.clue);
    attroff(A_UNDERLINE | A_BOLD);

    // Deactivate tile color theme
    attroff(A_COLOR);

    if(item.is_highlighted) {
        tdraw_highlight_box(clue_length, left_padding_size, column, row);
    }
}

void tdraw_tile_padding(int tile_length, int column, int row) {
    // char padding_string[tile_length];
    // memset(padding_string, ' ', tile_length);
    mvhline(row, column, ' ', tile_length);
    // printf("%s%s", color_to_ansi_background((enum color)WHITE), padding_string);
}

void tdraw_highlight_box(int tile_length, int left_padding_size, int column, int row) {
    attron(COLOR_PAIR(HIGHLIGHTED_COLOR_PAIR));

    // // Top line
    // mvhline(row, column, 0, tile_length - 1);
    // // Bottom line
    // mvhline(row + 2, column, 0, tile_length - 1);
    // // Left line
    // mvvline(row, column, 0, 3);
    // // Right Line
    // mvvline(row, column + tile_length - 1, 0, 3);

    // mvaddch(row, column, ACS_ULCORNER);
    // mvaddch(row + 2, column, ACS_LLCORNER);
    // mvaddch(row, column + tile_length - 1, ACS_URCORNER);
    // mvaddch(row + 2, column + tile_length - 1, ACS_LRCORNER);
    // mvhline(row + 2, column + left_padding_size, '', tile_length);

    attroff(COLOR_PAIR(HIGHLIGHTED_COLOR_PAIR));
}