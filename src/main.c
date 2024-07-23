#include <curses.h>
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "../lib/tcanvas.h"
#include "../lib/connections.h"

int main() {
    citem items[16];

    cgroup group_1 = {
        .group_identifier=YELLOW,
        .category="YEARN",
        .group_guessed_correctly=false
    };
    cgroup group_2 = {
        .group_identifier=GREEN,
        .category="MAGAZINES",
        .group_guessed_correctly=false
    };
    cgroup group_3 = {
        .group_identifier=BLUE,
        .category="CHARACTERS IN BOND MOVIES",  
        .group_guessed_correctly=false
    };
    cgroup group_4 = {
        .group_identifier=PURPLE,
        .category="WORDS THAT PRECEDE \"POP\" IN MUSIC GENRES",
        .group_guessed_correctly=false
    };

    cboard board = {
        .groups={group_1, group_2, group_3, group_4},
        .items={
            {
                .board_placement=14,
                .clue="DESIRE",
                .group_indentifier=YELLOW,
            },
            {
                .board_placement=8,
                .clue="LONG",
                .group_indentifier=YELLOW,
            },
            {
                .board_placement=11,
                .clue="PINE",
                .group_indentifier=YELLOW,
            },
            {
                .board_placement=0,
                .clue="YEN",
                .group_indentifier=YELLOW,
            },
            {
                .board_placement=7,
                .clue="FORTUNE",
                .group_indentifier=GREEN,
            },
            {
                .board_placement=2,
                .clue="MAD",
                .group_indentifier=GREEN,
            },
            {
                .board_placement=13,
                .clue="NATURE",
                .group_indentifier=GREEN,
            },
            {
                .board_placement=5,
                .clue="O",
                .group_indentifier=GREEN,
            },
            {
                .board_placement=1,
                .clue="BOND",
                .group_indentifier=BLUE,
            },
            {
                .board_placement=9,
                .clue="M",
                .group_indentifier=BLUE,
            },
            {
                .board_placement=15,
                .clue="MONEYPENNY",
                .group_indentifier=BLUE,
            },
            {
                .board_placement=6,
                .clue="Q",
                .group_indentifier=BLUE,
            },
            {   
                .board_placement=12,
                .clue="BUBBLEGUM",
                .group_indentifier=PURPLE,
            },
            {
                .board_placement=4,
                .clue="EURO",
                .group_indentifier=PURPLE,
            },
            {
                .board_placement=10,
                .clue="K",
                .group_indentifier=PURPLE,
            },
            {
                .board_placement=3,
                .clue="POWER",
                .group_indentifier=PURPLE,
            },
        },
        .selected_items_count = 0,
    };

    game_loop(board);
}

