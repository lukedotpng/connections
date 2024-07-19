#include <curses.h>
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <sys/_types/_null.h>
#include "../lib/tcanvas.h"
#include "../lib/connections.h"

int main() {
	// 
	// [Apple Pie] [    ] [    ] [    ]
	// [    ] [    ] [    ] [    ] 
	// [    ] [    ] [    ] [    ] 
	// [    ] [    ] [    ] [    ] 
	//
    gitem items[16];

    cgroup group_1 = {
        .group_identifier=1,
        .category="YEARN",
        .items={{
            .board_placement=14,
            .clue="DESIRE",
            .group_indentifier=1,
        },
        {
            .board_placement=8,
            .clue="LONG",
            .group_indentifier=1,
        },
        {
            .board_placement=11,
            .clue="PINE",
            .group_indentifier=1,
        },
        {
            .board_placement=0,
            .clue="YEN",
            .group_indentifier=1,
        }},
        .group_guessed_correctly=false
    };
    cgroup group_2 = {
        .group_identifier=2,
        .category="MAGAZINES",
        .items={{
            .board_placement=7,
            .clue="FORTUNE",
            .group_indentifier=1,
        },
        {
            .board_placement=2,
            .clue="MAD",
            .group_indentifier=1,
        },
        {
            .board_placement=13,
            .clue="NATURE",
            .group_indentifier=1,
        },
        {
            .board_placement=5,
            .clue="O",
            .group_indentifier=1,
        }},
        .group_guessed_correctly=false
    };
    cgroup group_3 = {
        .group_identifier=3,
        .category="CHARACTERS IN BOND MOVIES",
        .items={{
            .board_placement=1,
            .clue="BOND",
            .group_indentifier=1,
        },
        {
            .board_placement=9,
            .clue="M",
            .group_indentifier=1,
        },
        {
            .board_placement=15,
            .clue="MONEYPENNY",
            .group_indentifier=1,
        },
        {
            .board_placement=6,
            .clue="Q",
            .group_indentifier=1,
        }},
        .group_guessed_correctly=false
    };
    cgroup group_4 = {
        .group_identifier=4,
        .category="WORDS THAT PRECEDE \"POP\" IN MUSIC GENRES",
        .items={{
            .board_placement=12,
            .clue="BUBBLEGUM",
            .group_indentifier=1,
        },
        {
            .board_placement=4,
            .clue="EURO",
            .group_indentifier=1,
        },
        {
            .board_placement=10,
            .clue="K",
            .group_indentifier=1,
        },
        {
            .board_placement=3,
            .clue="POWER",
            .group_indentifier=1,
        }},
        .group_guessed_correctly=false
    };
    cboard board = {
        .groups={group_1, group_2, group_3, group_4}
    };

    // SCREEN* game_screen = newterm("Connections", NULL, NULL);
    // initscr();
    // cbreak(); 
    // noecho();

    bool game_active = true;
    while(game_active) {
        // delscreen(0);
        char input;
	    tdraw_board(board);
        // input = wgetch(stdscr);

        game_active = false;
        // TODO
        // - clear screen for each loop
        // - process inputs
    }
}

