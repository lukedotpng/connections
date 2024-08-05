#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/connections_json_parser.h"
#include "../lib/connections.h"

int parse_json(char* json_string, cboard* board) {
    int json_string_length = strlen(json_string);
    char categories_string[11];

    parse_categories(json_string, board); 
    parse_items(json_string, board);

    return 0;
}

void parse_categories(char *json_string, cboard *board) {
    // Loop to parse all categories
    char* title_key_string = strstr(json_string, "\"title\"") + 9;
    for(int i = 0; i < 4; i++) {
        char* current_char = title_key_string;
        while (*current_char != '"') {
            current_char++;
        }
        int category_length = current_char - title_key_string;
        char* current_category = malloc(category_length + 1);
        strncpy(current_category, title_key_string, category_length);   
        board->groups[i].category = remove_utf8_chars(current_category);
        board->groups[i].identifier = i + 1;
        title_key_string = strstr(current_char, "\"title\"") + 9;
    }

    return;
}

void parse_items(char *json_string, cboard *board) {
    // Loop to parse all items
    char* item_key_string = strstr(json_string, "\"content\"") + 11;
    for(int i = 0; i < 16; i++) {
        char* current_char = item_key_string;
        while (*current_char != '"') {
            current_char++;
        }
        int item_length = current_char - item_key_string;
        char* current_item = malloc(item_length + 1);
        strncpy(current_item, item_key_string, item_length);   
        board->items[i].clue = current_item;
        item_key_string = strstr(current_char, "\"content\"") + 11;
    }

    char* item_placement_key_string = strstr(json_string, "\"position\"") + 11;
    for(int i = 0; i < 16; i++) {
        char* current_char = item_placement_key_string;
        while (isdigit(*current_char) > 0) {
            current_char++;
        }
        int item_placement_length = current_char - item_placement_key_string;
        char* current_item_placement_string = malloc(item_placement_length + 1);
        strncpy(current_item_placement_string, item_placement_key_string, item_placement_length);   
        int current_item_placement = atoi(current_item_placement_string);
        board->items[i].board_placement = current_item_placement;
        board->items[i].group_indentifier = (i / 4) + 1;
        item_placement_key_string = strstr(current_char, "\"position\"") + 11;
    }

    return;
}

char* remove_utf8_chars(char* string) {
    int length = strlen(string);
    int positions_to_remove_count = 0;
    for(int i = 0; i < length; i++) {
        if((int)string[i] == -30 || (int)string[i] == -128) {
            positions_to_remove_count++;
        }
        if((int)string[i] < 0) {
            switch((int)string[i]) {
                case -100:
                case -99:
                    string[i] = '"';
                    break;
                case -103:
                    string[i] = '\'';
                    break;
            }
        }
    }

    if(positions_to_remove_count == 0) {
        return string;
    }

    char* new_string = malloc(length - positions_to_remove_count);
    int new_string_index = 0;
    for(int i = 0; i < length; i++) {
        if((int)string[i] >= 0) {
            new_string[new_string_index] = string[i];
            new_string_index++;
        }
    }
    
    return new_string;
}