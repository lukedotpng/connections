#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <ncurses.h>
#include <stdbool.h>

#define YELLOW_GROUP   1
#define GREEN_GROUP    2
#define BLUE_GROUP     3
#define PURPLE_GROUP   4

#define QUIT_GAME      'q'
#define TOGGLE_TILE_HIGHLIGHT ' '
#define W_KEY          'w'
#define S_KEY          's'
#define D_KEY          'd'
#define A_KEY          'a'
#define SUBMIT_GUESS    10

typedef struct group_item {
    int group_indentifier;
    char* clue;
    int board_placement;
    bool is_selected;
    bool is_highlighted;
} citem;

typedef struct category_group {
    char* category;
    int group_identifier;
    bool group_guessed_correctly;
} cgroup;

typedef struct connections_board {
    cgroup groups[4];
    citem items[16];
    citem* selected_items[4];
    int selected_items_count;
    int solved_groups[4];
    int current_highlighted_tile;
    int previous_highlighted_tile;
    bool game_active;
} cboard;

int game_loop(cboard board);

void handle_key_press(cboard* board, char input);

void handle_tile_highlight_toggle(cboard* board);
void handle_guess_submit(cboard* board);
void handle_quit(cboard* board);
void handle_up_movement(cboard* board);
void handle_down_movement(cboard* board);
void handle_right_movement(cboard* board);
void handle_left_movement(cboard* board);

#endif