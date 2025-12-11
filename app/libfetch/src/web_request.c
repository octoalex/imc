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
    const size_t size = number * element;
    if (buffer->data == nullptr) {
        *buffer = alloc_byte_array(size);
    } else if (buffer->size != size) {
        resize_byte_array(buffer, size);
    }
    memcpy(buffer->data, contents, size);
    return size;
}

/// Helper that converts a possible CURLcode to a web_request_status
static web_request_status curl_code_to_web_request_status(const CURLcode code) {
    switch (code) {
    case CURLE_OK:
        return WEB_REQUEST_STATUS_OK;

    case CURLE_FAILED_INIT:
        return WEB_REQUEST_STATUS_SETUP_ERROR;

    case CURLE_URL_MALFORMAT:
        return WEB_REQUEST_STATUS_BAD_URL;

    case CURLE_COULDNT_RESOLVE_HOST:
        return WEB_REQUEST_STATUS_HOST_UNREACHABLE;

    case CURLE_COULDNT_CONNECT:
    case CURLE_SEND_ERROR:
    case CURLE_RECV_ERROR:
        return WEB_REQUEST_STATUS_CONNECT_ERROR;

    case CURLE_WEIRD_SERVER_REPLY:
    case CURLE_HTTP2:
    case CURLE_PARTIAL_FILE:
    case CURLE_HTTP_RETURNED_ERROR:
    case CURLE_BAD_DOWNLOAD_RESUME:
    case CURLE_TOO_MANY_REDIRECTS:
    case CURLE_GOT_NOTHING:
    case CURLE_HTTP3:
    case CURLE_TOO_LARGE:
    case CURLE_SEND_FAIL_REWIND:
        return WEB_REQUEST_STATUS_DOWNLOAD_ERROR;

    case CURLE_REMOTE_ACCESS_DENIED:
    case CURLE_REMOTE_FILE_NOT_FOUND:
        return WEB_REQUEST_STATUS_FILE_INACCESSIBLE;

    case CURLE_OPERATION_TIMEDOUT:
        return WEB_REQUEST_STATUS_TIMEOUT;

    case CURLE_SSL_CONNECT_ERROR:
    case CURLE_PEER_FAILED_VERIFICATION:
    case CURLE_BAD_CONTENT_ENCODING:
    case CURLE_USE_SSL_FAILED:
    case CURLE_SSL_ENGINE_INITFAILED:
    case CURLE_SSL_ISSUER_ERROR:
        return WEB_REQUEST_STATUS_SSL_ERROR;

    case CURLE_WRITE_ERROR:
    case CURLE_OUT_OF_MEMORY:
        return WEB_REQUEST_STATUS_OUT_OF_MEMORY;

    default:
        return WEB_REQUEST_STATUS_OTHER;
    }
}

web_request_status web_request(const char *url, byte_array *buffer, const unsigned long timeout) {
    if (!strncasecmp(url, HTTP_URL_START, strlen(HTTP_URL_START))
        && !strncasecmp(url, HTTPS_URL_START, strlen(HTTPS_URL_START))) {
        return WEB_REQUEST_INVALID_PROTOCOL;
    }

    CURL *client = curl_easy_init();
    if (client == nullptr) {
        return false;
    }
    curl_easy_setopt(client, CURLOPT_URL, url);
    curl_easy_setopt(client, CURLOPT_WRITEFUNCTION, write_to_memory);
    if (timeout != 0) {
        curl_easy_setopt(client, CURLOPT_TIMEOUT_MS, timeout < 0 ? DEFAULT_TIMEOUT : timeout);
    }

    curl_easy_setopt(client, CURLOPT_FAILONERROR, 1);
    curl_easy_setopt(client, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(client, CURLOPT_USERAGENT, CURL_USERAGENT);

    const CURLcode result = curl_easy_perform(client);
    curl_easy_cleanup(client);
    return curl_code_to_web_request_status(result);
}

web_request_status setup_web_request() {
    const CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    return curl_code_to_web_request_status(result);
}

void cleanup_web_request() {
    curl_global_cleanup();
}
