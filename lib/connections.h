#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <stdbool.h>

#define YELLOW   1
#define GREEN    2
#define BLUE     3
#define PURPLE   4

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
} cboard;

int game_loop(cboard board);

#endif