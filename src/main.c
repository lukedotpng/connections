#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "../lib/connections.h"
#include "../lib/http_request.h"
#include "../lib/connections_json_parser.h"

int main() {

    time_t raw_time;
    time(&raw_time);
    struct tm* current_time = localtime(&raw_time);

    int current_year = current_time->tm_year + 1900;
    int current_month = current_time->tm_mon + 1;
    int current_day = current_time->tm_mday;
    char* daily_connections_url = malloc(59);
    if(current_month < 10 && current_day < 10) {
        snprintf(daily_connections_url, 59, "https://www.nytimes.com/svc/connections/v2/%d-0%d-0%d.json", current_year, current_month, current_day);
    }
    else if(current_month < 10) {
        snprintf(daily_connections_url, 59, "https://www.nytimes.com/svc/connections/v2/%d-0%d-%d.json", current_year, current_month, current_day);
    }
    else if(current_day < 10) {
        snprintf(daily_connections_url, 59, "https://www.nytimes.com/svc/connections/v2/%d-%d-0%d.json", current_year, current_month, current_day);
    }

    printf("%s\n", daily_connections_url);

    char* json_string = get_request(daily_connections_url);
    cboard board = (cboard){0};
    board.game_active = true;
    board.selected_items_count = 0;
    board.solved_groups_count = 0;
    parse_json(json_string, &board);
    game_loop(board);
}

