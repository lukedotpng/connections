#include "../lib/http_request.h"
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

void init_curl() {
    curl_global_init(0);
}

size_t write_callback(char *data, size_t size, size_t data_size, void* user_data) {
    struct memory* user_data_chunk = (struct memory*) user_data;    

    char* new_user_data_ptr = realloc(user_data_chunk->data, user_data_chunk->size + data_size + 1);
    if(!new_user_data_ptr) {
        return 0; // no memory
    }
    
    user_data_chunk->data = new_user_data_ptr;
    memcpy(&(user_data_chunk->data[user_data_chunk->size]), data, data_size);
    user_data_chunk->size += data_size;
    user_data_chunk->data[user_data_chunk->size] = 0;

    return data_size;
}

char* get_request(char* url) {
    struct memory data_chunk = {0};

    CURL* curl_handle = curl_easy_init();

    if(curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &data_chunk);

        curl_easy_perform(curl_handle);

        curl_easy_cleanup(curl_handle);
        curl_handle = NULL;
        return data_chunk.data;
    }
}