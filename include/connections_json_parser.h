#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "../include/connections.h"

int parse_json(char* json_string, cboard* board);
void parse_categories(char* json_string, cboard* board);
void parse_items(char* json_string, cboard* board);
char* remove_utf8_chars(char* string);

#endif