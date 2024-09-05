#ifndef HTTP_REQUEST
#define HTTP_REQUEST

#include <curl/curl.h>

struct memory {
    char* data;
    size_t size;
};

void init_curl();
char* get_request(char* url);

#endif