#include "../lib/connections.h"
#include "../lib/tcanvas.h"
#include <curses.h>
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

    clear();

    while (board.game_active) {
        tdraw_board(&board);
        refresh();

        handle_key_press(&board);

        board.previous_highlighted_tile = board.current_highlighted_tile;
    }   

    printf("\n\n");
    move(0, 0);
    curs_set(1);
    reset_shell_mode();
    return 0;
}

void handle_tile_select_toggle(cboard* board) {
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

    int guess_check_result = check_guess(board);

    for(int i = 0; i < 4; i++) {
        if(guess_check_result > 0) {
            board->selected_items[i]->is_hidden = true;
        }
        board->selected_items[i]->is_selected = false;
        board->selected_items[i] = NULL;
    }

    if(guess_check_result > 0) {
        board->solved_groups[board->solved_groups_count] = guess_check_result;
        board->solved_groups_count++;
        
        int new_items_array_size = 16 - (board->solved_groups_count * 4);
        citem sorted_items[new_items_array_size];

        int sorted_array_index = 0;
        for(int i = 0; i < (16 - ((board->solved_groups_count - 1) * 4)); i++) {
            if(board->items[i].is_hidden) {
                continue;
            }
            sorted_items[sorted_array_index] = board->items[i];
            sorted_array_index++;
        }
        memcpy(board->items, sorted_items, sizeof(citem) * new_items_array_size);

        board->items[0].is_highlighted = true;
        board->current_highlighted_tile = 0;
        clear();
    }

    board->selected_items_count = 0;
}

int check_guess(cboard* board) {
    int group_to_check = board->selected_items[0]->group_indentifier;
    for(int i = 1; i < 4; i++) {
        if(board->selected_items[i]->group_indentifier != group_to_check) {
            return 0;
        }
    }
    return group_to_check;
}

void handle_key_press(cboard* board) {
        char input = wgetch(stdscr);

    switch (input) {
        // Handle arrow keys
        case ESCAPE_SEQUENCE_START:
            wgetch(stdscr); // Skip over '[' part of arrow key sequence 
            input = wgetch(stdscr);
            handle_arrow_keys(board, input);
            break;
        // Stop game loop
        case Q_KEY_LOWER:
        case Q_KEY_UPPER:
            handle_quit(board);
            break;
        // Highlight tile
        case TOGGLE_TILE_HIGHLIGHT:
            handle_tile_select_toggle(board);
            break;
        // Submit guess
        case SUBMIT_GUESS:
            handle_guess_submit(board);
            break;
        // Handle up movement
        case W_KEY_LOWER:
        case W_KEY_UPPER:
            handle_up_movement(board);
            break;
        // Handle down movement
        case S_KEY_LOWER:
        case S_KEY_UPPER:
            handle_down_movement(board);
            break;
        // Handle right movement
        case D_KEY_LOWER:
        case D_KEY_UPPER:
            handle_right_movement(board);
            break;
        // Handle left movement
        case A_KEY_LOWER:
        case A_KEY_UPPER:
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

void handle_arrow_keys(cboard* board, char input) {
    switch (input) {
        case UP_ARROW:
            handle_up_movement(board);
            break;
        case DOWN_ARROW:
            handle_down_movement(board);
            break;
        case RIGHT_ARROW:
            handle_right_movement(board);
            break;
        case LEFT_ARROW:
            handle_left_movement(board);
            break;
    }
}

void handle_up_movement(cboard* board) {
    if(board->solved_groups_count == 3) {
        return;
    }

    if (board->current_highlighted_tile <= 3) {
        board->current_highlighted_tile += (12 - (board->solved_groups_count * 4));
    } else {
        board->current_highlighted_tile -= 4;
    }
}

void handle_down_movement(cboard* board) {
    if(board->solved_groups_count == 3) {
        return;
    }

    if (board->current_highlighted_tile >= (12 - (board->solved_groups_count * 4))) {
        board->current_highlighted_tile -= (12 - (board->solved_groups_count * 4));
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