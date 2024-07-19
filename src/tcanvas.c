#include "../lib/tcanvas.h"
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int initialize_canvas(int height);

void draw(const char* string, enum color text_color, enum color background_color) {

}

void tdraw_board(const cboard board) {
    gitem all_items_unsorted[16];
    gitem all_items_sorted[16];
    
    // Move all items into one array for easier handling
    // Using one iterator just cause :D
    for(int i = 0; i < 16; i+=4) {
        all_items_unsorted[i] = board.groups[i / 4].items[i % 4];
        all_items_unsorted[i + 1] = board.groups[i / 4].items[(i + 1) % 4];
        all_items_unsorted[i + 2] = board.groups[i / 4].items[(i + 2) % 4];
        all_items_unsorted[i + 3] = board.groups[i / 4].items[(i + 3) % 4];
    }

    // Finding longest clue length to determine the size of all tiles
    // using unsigned here isnt really needed, but extra safety since strlen returns unsigned
    unsigned int longest_item_length = 0;
    for(int i = 0; i < 16; i++) {
        if(strlen(all_items_unsorted[i].clue) > longest_item_length) {
            longest_item_length = strlen(all_items_unsorted[i].clue);
        }
        // Put items in sorted array based on board placement
        all_items_sorted[all_items_unsorted[i].board_placement] = all_items_unsorted[i];
    }
    // Add extra padding to the tile size
    int tile_length = longest_item_length + 2;
    int tile_height = 3;
    // SPACE BUFFER
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\e7");

    int item_count = 0;
    for(int row = 0; row < 4; row++) {
        // Draw blamk above
        for(int col = 0; col < 4; col++) {
            printf("\e8");
            tdraw_tile(all_items_sorted[item_count], tile_length, tile_height, col, row);
            item_count++;
        }
    }
    printf("\n");
}

void tdraw_tile(const gitem item, int length, int height, int column_index, int row_index) {
    int clue_length = strlen(item.clue);
    int clue_padding = length - clue_length;
    // Some magic numbers dont mind these :)
    int column = (column_index * (length + 2)) + 1;
    int row = 17 - (row_index * 4);

    // Move cursor to correct column and row 
    printf("\e[%dG\e[%dA", column, row);
    tdraw_tile_padding(length);
    // Move cursor back to correct column, and down one row
    printf("\e[%dG\e[1B", column);
    int left_padding_size = clue_padding / 2;
    int right_padding_size = clue_padding - left_padding_size;
    char left_padding[left_padding_size];
    char right_padding[right_padding_size];
    memset(left_padding, ' ', left_padding_size);
    memset(right_padding, ' ', right_padding_size);
    printf("%s%s%s%s%s", color_to_ansi_text((enum color)BLACK), color_to_ansi_background((enum color)WHITE), left_padding, item.clue, right_padding);
    // Move cursor back to correct column, and down one row
    printf("\e[%dG\e[1B", column);
    tdraw_tile_padding(length);
}

void tdraw_tile_padding(int tile_length) {
    char padding_string[tile_length];
    memset(padding_string, ' ', tile_length);
    printf("%s%s", color_to_ansi_background((enum color)WHITE), padding_string);
}

const char* color_to_ansi_text(enum color color) {
    switch (color) {
        case BLACK:
            return "\e[30m";
        case RED: 
            return "\e[31m";
        case GREEN:
            return "\e[32m";
        case YELLOW:
            return "\e[33m";
        case BLUE:
            return "\e[34m";
        case MAGENTA:
            return "\e[35m";
        case CYAN: 
            return "\e[36m";
        case WHITE:
            return  "\e[37m";
        case DEFAULT: 
            return "\e[39m";
        case RESET:
            return "\e[0m";
    }
}

const char* color_to_ansi_background(enum color color) {
    switch (color) {
        case BLACK:
            return "\e[40m";
        case RED: 
            return "\e[41m";
        case GREEN:
            return "\e[42m";
        case YELLOW:
            return "\e[43m";
        case BLUE:
            return "\e[44m";
        case MAGENTA:
            return "\e[45m";
        case CYAN: 
            return "\e[46m";
        case WHITE:
            return "\e[47m";
        case DEFAULT: 
            return "\e[49m";
        case RESET:
            return "\e[0m";
    }
}