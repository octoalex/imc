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

// Error Messages
const char *const ERROR_MESSAGE_BAD_PROTOCOL = "The protocol is not supported!";

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
    if (strncasecmp(url, HTTP_URL_START, strlen(HTTP_URL_START)) != 0
        && strncasecmp(url, HTTPS_URL_START, strlen(HTTPS_URL_START)) != 0) {
        const web_request_status status = {
            .code = WEB_REQUEST_STATUS_UNSUPPORTED_PROTOCOL,
            .message = nullptr
        };
        return status;
    }

    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
        if (result != CURLE_OK) {
            const web_request_status status = {
                .code = WEB_REQUEST_STATUS_FAILED,
                .message = strdup(curl_easy_strerror(result))
            };
            return status;
        }
    }

    CURL *client = curl_easy_init();
    if (client == nullptr) {
        const web_request_status status = {
            .code = WEB_REQUEST_STATUS_FAILED,
            .message = nullptr
        };
        return status;
    }

    char *message = calloc(CURL_ERROR_SIZE + 1, sizeof(char));
    // set the options
    curl_easy_setopt(client, CURLOPT_URL, url);
    curl_easy_setopt(client, CURLOPT_WRITEFUNCTION, write_to_memory);
    curl_easy_setopt(client, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(client, CURLOPT_FAILONERROR, true);
    curl_easy_setopt(client, CURLOPT_USERAGENT, CURL_USERAGENT);
    curl_easy_setopt(client, CURLOPT_ERRORBUFFER, message);
    if (timeout != -1) {
        curl_easy_setopt(client, CURLOPT_TIMEOUT_MS, timeout == 0 ? DEFAULT_TIMEOUT : timeout);
    }

    const CURLcode result = curl_easy_perform(client);
    curl_easy_cleanup(client);
    const web_request_status status = {
        .code = result == CURLE_OK ? WEB_REQUEST_STATUS_SUCCESS :
            (result == CURLE_URL_MALFORMAT ? WEB_REQUEST_STATUS_BAD_URL : WEB_REQUEST_STATUS_FAILED),
        .message = message
    };
    return status;
}

void cleanup_web_request() {
    curl_global_cleanup();
}
