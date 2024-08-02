#include "../lib/tcanvas.h"
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

    int item_count = 0;
    int placement_index = 0;
    for(int row = board->solved_groups_count; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            if(board->items[item_count].is_hidden == false) {
                tdraw_tile(board->items[item_count], tile_length, row, placement_index);
                placement_index++;
            }
            item_count++;
        }
    }

    for(int i = 0; i < board->solved_groups_count; i++) {
        tdraw_guessed_row(board->groups[board->solved_groups[i] - 1], i, tile_length);
    }
    // printf("\n");
}

void tdraw_tile(const citem item, int length, int row, int board_placement) {
    int clue_length = strlen(item.clue);
    int clue_padding = length - clue_length;

    // 0  1  2  3
    // 4  5  6  7 
    // 8  9  10 11 
    // 12 13 14 15 
    int column = (board_placement % 4) * (length + 2);
    row *= 4;

    int left_padding_size = clue_padding / 2;
    int right_padding_size = clue_padding - left_padding_size;


    if(item.is_selected) {
        attron(COLOR_PAIR(SELECTED_COLOR_PAIR));
    } else {
        attron(COLOR_PAIR(TILE_COLOR_PAIR));
    }

    // Upper padding
    tdraw_padding(length, column, row);
    // Left padding
    tdraw_padding(left_padding_size, column, row + 1);
    // Right padding
    tdraw_padding(right_padding_size, column + (length - right_padding_size), row + 1);
    // Lower padding
    tdraw_padding(length, column, row + 2);
    
    // Clue
    if(item.is_highlighted) {
        attron(A_UNDERLINE | A_BOLD);
    }
    mvprintw(row + 1, column + left_padding_size, item.clue);
    attroff(A_UNDERLINE | A_BOLD);

    // Deactivate tile color theme
    attroff(A_COLOR);
}

void tdraw_padding(int length, int column, int row) {
    // char padding_string[tile_length];
    // memset(padding_string, ' ', tile_length);
    mvhline(row, column, ' ', length);
    // printf("%s%s", color_to_ansi_background((enum color)WHITE), padding_string);
}

void tdraw_guessed_row(cgroup group, int row, int length) {
    attron(COLOR_PAIR(group.identifier));

    int row_length = (length * 4) + 6;
    row *= 4;
    int category_length = strlen(group.category);
    int row_padding = row_length - category_length;

    int left_padding_size = row_padding / 2;
    int right_padding_size = row_padding - left_padding_size;

    tdraw_padding(row_length, 0, row);
    tdraw_padding(left_padding_size, 0, row + 1);
    tdraw_padding(right_padding_size, row_length - right_padding_size, row + 1);
    tdraw_padding(row_length, 0, row + 2);

    mvprintw(row + 1, left_padding_size, group.category);

    attroff(A_COLOR);
}