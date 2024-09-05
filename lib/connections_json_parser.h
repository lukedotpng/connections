#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "../lib/connections.h"

int parse_json(char* json_string, cboard* board);
void parse_categories(char* json_string, cboard* board);
void parse_items(char* json_string, cboard* board);
char* format_punctuation(char* string);

#endif