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

    board.items[0].is_highlighted = true;
    board.current_highlighted_tile = 0;
    char input;

    clear();

    while (board.game_active) {
        tdraw_board(&board);
        refresh();

        input = wgetch(stdscr);
        handle_key_press(&board, input);

        board.previous_highlighted_tile = board.current_highlighted_tile;
    }   

    printf("\n\n");

    curs_set(1);
    reset_shell_mode();
    return 0;
}

void handle_key_press(cboard* board, char input) {
        switch (input) {
        // Stop game loop
        case QUIT_GAME:
            handle_quit(board);
            break;
        // Highlight tile
        case TOGGLE_TILE_HIGHLIGHT:
            handle_tile_highlight_toggle(board);
            break;
        // Submit guess
        case SUBMIT_GUESS:
            handle_guess_submit(board);
            break;
        // Handle up movement
        case W_KEY:
            handle_up_movement(board);
            break;
        // Handle down movement
        case S_KEY:
            handle_down_movement(board);
            break;
        // Handle right movement
        case D_KEY:
            handle_right_movement(board);
            break;
        // Handle left movement
        case A_KEY:
            handle_left_movement(board);
            break;
        default:
            break;
    }
    board->items[board->previous_highlighted_tile].is_highlighted = false;
    board->items[board->current_highlighted_tile].is_highlighted = true;
}

void handle_quit(cboard* board) {
    board->game_active = false;
}

void handle_tile_highlight_toggle(cboard* board) {
    if(board->items[board->current_highlighted_tile].is_selected) {
        citem* new_selected_items[4];
        int selected_items_index = 0;
        for(int i = 0; i < board->selected_items_count; i++) {
            if(board->selected_items[i]->is_highlighted) {
                board->selected_items[i]->is_selected = false;
                continue;
            }
            new_selected_items[selected_items_index] = board->selected_items[i];
            selected_items_index++;
        }
        memcpy(board->selected_items, new_selected_items, 4 * sizeof(citem*));
        board->selected_items_count = selected_items_index;

        // for(int i = 0; i < selected_items_index; i++) {
        //     free(new_selected_items[i]);
        // }
    }
    else {
        if(board->selected_items_count == 4) {
            return;
        }
        board->selected_items[board->selected_items_count] = &board->items[board->current_highlighted_tile];
        board->selected_items[board->selected_items_count]->is_selected = true;
        board->selected_items_count++;
    }
}

void handle_guess_submit(cboard* board) {
    if(board->selected_items_count < 4) {
        return;
    }

    for(int i = 0; i < board->selected_items_count; i++) {
        board->selected_items[i]->is_selected = false;
        board->selected_items[i] = NULL;
    }
    board->selected_items_count = 0;
}

void handle_up_movement(cboard* board) {
    if (board->current_highlighted_tile <= 3) {
        board->current_highlighted_tile += 12;
    } else {
        board->current_highlighted_tile -= 4;
    }
}

void handle_down_movement(cboard* board) {
    if (board->current_highlighted_tile >= 12) {
        board->current_highlighted_tile -= 12;
    } else {
        board->current_highlighted_tile += 4;
    }
}

void handle_right_movement(cboard* board) {
    if (board->current_highlighted_tile == 3 || board->current_highlighted_tile == 7 || board->current_highlighted_tile == 11 || board->current_highlighted_tile == 15) {
        board->current_highlighted_tile -= 3;
    } else {
        board->current_highlighted_tile += 1;
    }    
}

void handle_left_movement(cboard* board) {
    if (board->current_highlighted_tile == 0 || board->current_highlighted_tile == 4 || board->current_highlighted_tile == 8 || board->current_highlighted_tile == 12) {
        board->current_highlighted_tile += 3;
    } else {
        board->current_highlighted_tile -= 1;
    }
}