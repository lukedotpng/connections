#include "../lib/connections.h"
#include "../lib/tcanvas.h"
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int game_loop(cboard board) {
    initialize_canvas();

    citem sorted_items[16];

    for(int i = 0; i < 16; i++) {
        sorted_items[board.items[i].board_placement] = board.items[i];
    }
    memcpy(board.items, sorted_items, sizeof(board.items));

    bool game_active = true;
    board.items[0].is_highlighted = true;
    board.current_highlighted_tile = 0;
    char input;

    clear();

    while (game_active) {
        tdraw_board(&board);
        refresh();

        input = wgetch(stdscr);

        int prev_highlighted_tile = board.current_highlighted_tile;

        switch (input) {
            case 'q':
                game_active = false;
                break;
            case ' ':
                if(board.items[board.current_highlighted_tile].is_selected) {
                    citem* new_selected_items[4];
                    int selected_items_index = 0;
                    for(int i = 0; i < board.selected_items_count; i++) {
                        if(board.selected_items[i]->is_highlighted) {
                            board.selected_items[i]->is_selected = false;
                            continue;
                        }
                        new_selected_items[selected_items_index] = board.selected_items[i];
                        selected_items_index++;
                    }
                    memcpy(board.selected_items, new_selected_items, 4 * sizeof(citem*));
                    board.selected_items_count = selected_items_index;

                    // for(int i = 0; i < selected_items_index; i++) {
                    //     free(new_selected_items[i]);
                    // }
                }
                else {
                    if(board.selected_items_count == 4) {
                        break;
                    }
                    board.selected_items[board.selected_items_count] = &board.items[board.current_highlighted_tile];
                    board.selected_items[board.selected_items_count]->is_selected = true;
                    board.selected_items_count++;
                }
                break;
            case 10:
                if(board.selected_items_count < 4) {
                    break;
                }

                for(int i = 0; i < board.selected_items_count; i++) {
                    board.selected_items[i]->is_selected = false;
                    board.selected_items[i] = NULL;
                }
                board.selected_items_count = 0;
                break;
            case 0x41:
            case 'w':
                // Handle up movement
                if (board.current_highlighted_tile <= 3) {
                    board.current_highlighted_tile += 12;
                } else {
                    board.current_highlighted_tile -= 4;
                }
                break;
            case 0x42:
            case 's':
                // Handle down movement
                if (board.current_highlighted_tile >= 12) {
                    board.current_highlighted_tile -= 12;
                } else {
                    board.current_highlighted_tile += 4;
                }
                break;
            case 0x43:
            case 'd':
                // Handle right movement
                if (board.current_highlighted_tile == 3 || board.current_highlighted_tile == 7 || board.current_highlighted_tile == 11 || board.current_highlighted_tile == 15) {
                    board.current_highlighted_tile -= 3;
                } else {
                    board.current_highlighted_tile += 1;
                }
                break;
            case 0x44:
            case 'a':
                // Handle left movement
                if (board.current_highlighted_tile == 0 || board.current_highlighted_tile == 4 || board.current_highlighted_tile == 8 || board.current_highlighted_tile == 12) {
                    board.current_highlighted_tile += 3;
                } else {
                    board.current_highlighted_tile -= 1;
                }
                break;
            default:
                break;
        }
        board.items[prev_highlighted_tile].is_highlighted = false;
        board.items[board.current_highlighted_tile].is_highlighted = true;
    }   

    printf("\n\n");

    curs_set(1);
    reset_shell_mode();
    return 0;
}
