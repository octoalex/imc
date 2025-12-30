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
 * Created by octoalex on 24/12/2025.
 */

#include <imc/fetch/fetch.h>

#include <imc/fetch/web_request.h>
#include <imc/common/file_utils.h>
#include <imc/fetch/hash.h>
#include <string.h>

// Cache errors
const char *const ERROR_MESSAGE_NO_READ_CACHE = "The cache is not readable!";
const char *const ERROR_MESSAGE_NO_WRITE_CACHE = "The cache is not writeable!";
const char *const ERROR_MESSAGE_NO_READ_WRITE_CACHE = "The cache is neither readable or writable!";
const char *const ERROR_MESSAGE_NO_DIRECTORY_CACHE = "The cache's directory is inaccessible!";

// Argument errors
const char *const ERROR_MESSAGE_BAD_ARRAY = "Both the path and the array pointer were null!";
const char *const ERROR_MESSAGE_BAD_PROTOCOL = "The protocol is not supported!";

// Download errors
const char *const ERROR_MESSAGE_BAD_RESOURCE = "The downloaded file does not match the given hash!"
    "Consider checking if the resource is outdated";

static bool validate(const resource *resource, const byte_array *bytes);

fetch_status fetch(const resource *resource, byte_array *NULLABLE bytes) {
    if (resource->path == nullptr && bytes == nullptr) {
        const fetch_status status = {
            .code = FETCH_STATUS_BAD_ARGUMENTS,
            .message = strdup(ERROR_MESSAGE_BAD_ARRAY)
        };
        return status;
    }

    if (resource->path != nullptr) {
        const bool ex = is_file(resource->path);
        const bool re = can_read(resource->path);
        const bool wr = can_write(resource->path);
        // cache exists, but is not writeable or readable, thus the operation should fail
        if (ex && (!re || !wr)) {
            const fetch_status status = {
                .code = FETCH_STATUS_CACHING_FAILED,
                .message = strdup(
                    !re && !wr ? ERROR_MESSAGE_NO_READ_WRITE_CACHE :
                    !re ? ERROR_MESSAGE_NO_READ_CACHE : ERROR_MESSAGE_NO_WRITE_CACHE
                )
            };
            if (bytes != nullptr) { *bytes = EMPTY_BYTE_ARRAY; }
            return status;
        }

        // ensure that the cache location exists
        if (!ex) {
            char *parent = get_parent_dir(resource->path);
            if (!is_dir(parent)) {
                make_dirs(parent);
            }
            // check if the directory was created
            if (!is_dir(parent)) {
                const fetch_status status = {
                    .code = FETCH_STATUS_CACHING_FAILED,
                    .message = strdup(ERROR_MESSAGE_NO_DIRECTORY_CACHE)
                };
                if (bytes != nullptr) { *bytes = EMPTY_BYTE_ARRAY; }
                return status;
            }

            free(parent);
        } else {
            // fetch from cache!
            FILE *file = fopen(resource->path, "r");
            fseek(file, 0l, SEEK_END);
            const size_t size = ftell(file);
            rewind(file);
            byte_array buffer = alloc_byte_array(size);
            fread(buffer.data, sizeof(uint8_t), buffer.size, file);
            fclose(file);

            if (validate(resource, &buffer)) {
                if (bytes != nullptr) {
                    *bytes = buffer;
                } else {
                    free_byte_array(&buffer);
                }
                const fetch_status status = { .code = FETCH_STATUS_SUCCESS, .message = nullptr };
                return status;
            }
        }
    }

    // fetch from web
    byte_array fallback = EMPTY_BYTE_ARRAY;
    byte_array *buffer = bytes != nullptr ? bytes : &fallback;

    const web_request_status web_status = web_request(resource->url, buffer, DEFAULT_TIMEOUT);

    if (web_status.status != WEB_REQUEST_STATUS_SUCCESS) {
        fetch_status status = { };
        if (web_status.status == WEB_REQUEST_STATUS_UNSUPPORTED_PROTOCOL
            || web_status.status == WEB_REQUEST_STATUS_BAD_URL) {
            status.code = FETCH_STATUS_BAD_ARGUMENTS;
        } else {
            status.code = FETCH_STATUS_DOWNLOAD_FAILED;
        }
        if (web_status.status == WEB_REQUEST_STATUS_UNSUPPORTED_PROTOCOL) {
            status.message = strdup(ERROR_MESSAGE_BAD_PROTOCOL);
        } else {
            status.message = web_status.message;
        }
        free_byte_array(buffer);
        return status;
    }

    if (!validate(resource, buffer)) {
        const fetch_status status = {
            .code = FETCH_STATUS_BAD_RESOURCE,
            .message = strdup(ERROR_MESSAGE_BAD_RESOURCE)
        };
        free_byte_array(buffer);
        return status;
    }

    if (resource->path != nullptr) {
        // update buffer
        FILE *file = fopen(resource->path, "w");
        fwrite(buffer->data, sizeof(uint8_t), buffer->size, file);
        fclose(file);
    }

    // if bytes == nullptr, then fallback will contain the bytes, so it's important to free it as to avoid a memory leak
    // if bytes != nullptr, then fallback will be empty, and freeing it is not an issue
    free_byte_array(&fallback);
    const fetch_status status = { .code = FETCH_STATUS_SUCCESS, .message = nullptr };
    return status;
}

static bool validate(const resource *resource, const byte_array *bytes) {
    if (resource->size != 0 && resource->size != bytes->size) { return false; }
    return !is_hash_null(&resource->hash) && validate_bytes(bytes, &resource->hash);
}
