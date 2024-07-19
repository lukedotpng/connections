#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <stdbool.h>

typedef struct group_item {
    int group_indentifier;
    char* clue;
    int board_placement;
    bool is_selected;
    bool is_highlighted;
} gitem;

typedef struct category_group {
    char* category;
    int group_identifier;
    gitem items[4];
    bool group_guessed_correctly;
} cgroup;

typedef struct connections_board {
    cgroup groups[4];
} cboard;

#endif