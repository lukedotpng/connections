#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../lib/tcanvas.h"
#include "../lib/connections.h"
#include "../lib/http_request.h"
#include "../lib/connections_json_parser.h"

int main() {
    char* json_string = get_request("https://www.nytimes.com/svc/connections/v2/2024-08-05.json");
    cboard board = (cboard){0};
    board.game_active = true;
    board.selected_items_count = 0;
    board.solved_groups_count = 0;
    parse_json(json_string, &board);
    game_loop(board);
}

