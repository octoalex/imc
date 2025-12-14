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

#include <imc/fetch/web_request.h>

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

const char *const CURL_USERAGENT = "libcurl-agent/1.0";
const char *const HTTP_URL_START = "http://";
const char *const HTTPS_URL_START = "https://";

/// Helper that writes the bytes downloaded by curl to memory
static size_t write_to_memory(const void *contents, const size_t element, const size_t number, void *data) {
    byte_array *buffer = data;
    const size_t base = buffer->size;
    const size_t size = number * element;
    if (buffer->data == nullptr) {
        *buffer = alloc_byte_array(size);
        // insufficient data, abort function
        if (buffer->data == nullptr) {
            return CURL_WRITEFUNC_ERROR;
        }
    } else {
        resize_byte_array(buffer, buffer->size + size);
        // insufficient memory, abort function
        if (buffer->size == 0) {
            return CURL_WRITEFUNC_ERROR;
        }
    }
    memcpy(buffer->data + base, contents, size);
    return size;
}

web_request_status web_request(const char *url, byte_array *buffer, const unsigned long timeout) {
    web_request_status status = {
        .code = -1,
        .message = nullptr
    };
    if (strncasecmp(url, HTTP_URL_START, strlen(HTTP_URL_START)) != 0
        && strncasecmp(url, HTTPS_URL_START, strlen(HTTPS_URL_START)) != 0) {
        status.status = WEB_REQUEST_STATUS_UNSUPPORTED_PROTOCOL;
        return status;
    }

    static bool initialized = false;
    if (!initialized) {
        const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
        if (result != CURLE_OK) {
            status.status = WEB_REQUEST_STATUS_SETUP_FAILED;
            status.code = result;
            status.message = curl_easy_strerror(result);
            return status;
        }
    }

    CURL *client = curl_easy_init();
    if (client == nullptr) {
        status.status = WEB_REQUEST_STATUS_FAILED;
        return status;
    }

    // create error message buffer
    status.message = calloc(CURL_ERROR_SIZE + 1, sizeof(char));

    // set the options
    curl_easy_setopt(client, CURLOPT_URL, url);
    curl_easy_setopt(client, CURLOPT_WRITEFUNCTION, write_to_memory);
    curl_easy_setopt(client, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(client, CURLOPT_FAILONERROR, true);
    curl_easy_setopt(client, CURLOPT_USERAGENT, CURL_USERAGENT);
    curl_easy_setopt(client, CURLOPT_ERRORBUFFER, status.message);
    if (timeout != 0) {
        curl_easy_setopt(client, CURLOPT_TIMEOUT_MS, timeout < 0 ? DEFAULT_TIMEOUT : timeout);
    }

    const CURLcode result = curl_easy_perform(client);
    curl_easy_cleanup(client);
    status.code = result;
    switch (result) {
    case CURLE_OK:
        status.status = WEB_REQUEST_STATUS_SUCCESS;
        break;

    case CURLE_URL_MALFORMAT:
        status.status = WEB_REQUEST_STATUS_BAD_URL;
        break;

    case CURLE_FAILED_INIT:
        status.status = WEB_REQUEST_STATUS_SETUP_FAILED;
        break;

    case CURLE_OUT_OF_MEMORY:
    case CURLE_WRITE_ERROR:
        status.status = WEB_REQUEST_STATUS_OUT_OF_MEMORY;
        break;

    default:
        status.status = WEB_REQUEST_STATUS_FAILED;
        break;
    }
    return status;
}

void cleanup_web_request() {
    curl_global_cleanup();
}
