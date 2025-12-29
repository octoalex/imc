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
 * Created by octoalex on 25/12/2025.
 */

#include <imc/fetch/fetch.h>

#include <imc/common/pipe.h>
#include <string.h>

const char *const ERROR_MESSAGE_BAD_JSON = "Both the path and the json pointer were null!";
const char *const ERROR_MESSAGE_BAD_FILE = "Both the path and the file pointer were null!";

fetch_status fetch_json(const resource *resource, json_object *NULLABLE *json) {
    if (resource->path == nullptr && json == nullptr) {
        const fetch_status status = {
            .code = FETCH_STATUS_BAD_ARGUMENTS,
            .message = strdup(ERROR_MESSAGE_BAD_FILE)
        };
        return status;
    }

    byte_array bytes = EMPTY_BYTE_ARRAY;
    const fetch_status status = fetch(resource, &bytes);

    if (status.code != FETCH_STATUS_SUCCESS || json == nullptr) {
        if (json != nullptr) {
            *json = nullptr;
        }
    } else {
        resize_byte_array(&bytes, bytes.size + 1);
        *json = json_tokener_parse((char *)bytes.data);
        free_byte_array(&bytes);
    }
    free_byte_array(&bytes);
    return status;
}

fetch_status fetch_file(const resource *resource, FILE *NULLABLE *file) {
    if (resource->path == nullptr && file == nullptr) {
        const fetch_status status = {
            .code = FETCH_STATUS_BAD_ARGUMENTS,
            .message = strdup(ERROR_MESSAGE_BAD_FILE)
        };
        return status;
    }

    byte_array bytes = EMPTY_BYTE_ARRAY;
    const fetch_status status = fetch(resource, &bytes);

    if (status.code != FETCH_STATUS_SUCCESS || file == nullptr) {
        if (file != nullptr) {
            *file = nullptr;
        }
    } else if (resource->path != nullptr) {
        *file = fopen(resource->path, "r");
    } else {
        FILE *write;
        create_pipe(file, &write);
        fwrite(bytes.data, sizeof(uint8_t), bytes.size, write);
        fclose(write);
    }
    free_byte_array(&bytes);
    return status;
}
