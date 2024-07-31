#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <ncurses.h>
#include <stdbool.h>

#define YELLOW_GROUP   1
#define GREEN_GROUP    2
#define BLUE_GROUP     3
#define PURPLE_GROUP   4

#define TOGGLE_TILE_HIGHLIGHT ' ' // Space
#define Q_KEY_LOWER             'q'
#define Q_KEY_UPPER             'Q'

#define ESCAPE_SEQUENCE_START   '\033'
#define W_KEY_LOWER             'w'
#define W_KEY_UPPER             'W'
#define UP_ARROW                'A'
#define S_KEY_LOWER             's'
#define S_KEY_UPPER             'S'
#define DOWN_ARROW              'B'
#define D_KEY_LOWER             'd'
#define D_KEY_UPPER             'D'
#define RIGHT_ARROW             'C'
#define A_KEY_LOWER             'a'
#define A_KEY_UPPER             'A'
#define LEFT_ARROW              'D'
#define SUBMIT_GUESS            10 // Enter

typedef struct group_item {
    int group_indentifier;
    char* clue;
    int board_placement;
    bool is_selected;
    bool is_highlighted;
    bool is_hidden;
} citem;

typedef struct category_group {
    char* category;
    int identifier;
    bool guessed_correctly;
} cgroup;

typedef struct connections_board {
    cgroup groups[4];
    citem items[16];
    citem* selected_items[4];
    int selected_items_count;
    int solved_groups[4];
    int solved_groups_count;
    int current_highlighted_tile;
    int previous_highlighted_tile;
    bool game_active;
} cboard;

int game_loop(cboard board);


void handle_tile_highlight_toggle(cboard* board);
void handle_guess_submit(cboard* board);
int check_guess(cboard* board);

void handle_key_press(cboard* board);
void handle_quit(cboard* board);
void handle_arrow_keys(cboard*, char input);
void handle_up_movement(cboard* board);
void handle_down_movement(cboard* board);
void handle_right_movement(cboard* board);
void handle_left_movement(cboard* board);

#endif