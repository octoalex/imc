/* 
 * This file is part of octoalex's imc (https://github.com/octoalex/imc).
 * Copyright (c) 2025 octoalex.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Created by octoalex on 28/11/2025.
 */

#include <imc/fetch/fetch.h>

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

const char *const CURL_USERAGENT = "libcurl-agent/1.0";

static size_t write_to_memory(const void *contents, const size_t element, const size_t number, void *data) {
    void **tuple = data;
    const size_t size = number * element;
    *(uint8_t **)tuple[0] = calloc(number, element);
    *(size_t *)tuple[1] = size;
    memcpy(*(uint8_t **)tuple[0], contents, size);
    return size;
}

static CURLcode fetch_inner(CURL *client, const char *url, void *write_data, bool use_callback) {
    curl_easy_setopt(client, CURLOPT_URL, url);
    if (use_callback) {
        curl_easy_setopt(client, CURLOPT_WRITEFUNCTION, write_to_memory);
    }
    curl_easy_setopt(client, CURLOPT_WRITEDATA, write_data);
    curl_easy_setopt(client, CURLOPT_USERAGENT, CURL_USERAGENT);

    const CURLcode result = curl_easy_perform(client);
    curl_easy_cleanup(client);
    return result;
}

bool fetch(const char *url, uint8_t **data, size_t *size) {
    void **tuple = calloc(2, sizeof(void *));
    tuple[0] = data;
    tuple[1] = size;
    CURL *client = curl_easy_init();
    if (client == nullptr) {
        return false;
    }
    const CURLcode result = fetch_inner(client, url, tuple, true);
    return result == CURLE_OK;
}

bool fetch_to_file(const char *url, FILE *file) {
    CURL *client = curl_easy_init();
    if (client == nullptr) {
        return false;
    }
    const CURLcode result = fetch_inner(client, url, file, false);
    return result == CURLE_OK;
}

bool setup_fetch() {
    const CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    return res == CURLE_OK;
}

void shutdown_fetch() {
    curl_global_cleanup();
}
