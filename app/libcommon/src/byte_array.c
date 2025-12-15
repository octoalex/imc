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
 * Created by octoalex on 07/12/2025.
 */

#include <imc/common/byte_array.h>
#include <stdlib.h>
#include <string.h>

byte_array alloc_byte_array(const size_t size) {
    if (size == 0) {
        const byte_array empty = { nullptr, 0 };
        return empty;
    }
    const byte_array array = {
        .data = calloc(size, sizeof(uint8_t)),
        .size = size
    };
    return array;
}

void free_byte_array(byte_array *array) {
    free(array->data);
    array->data = nullptr;
    array->size = 0;
}

void resize_byte_array(byte_array *array, const size_t new_size) {
    uint8_t *new_data = realloc(array->data, new_size);
    if (new_data == nullptr) {
        // in this case, free
        free_byte_array(array);
        return;
    }
    for (size_t i = array->size; i < new_size; ++i) {
        new_data[i] = 0;
    }
    array->data = new_data;
    array->size = new_size;
}

byte_array copy_byte_array(const byte_array *base) {
    byte_array new = *base;
    new.data = malloc(base->size * sizeof(uint8_t));
    memcpy(new.data, base->data, new.size);
    return new;
}

byte_array from_c_string(const char *string) {
    const size_t size = strlen(string);
    const byte_array new = {
        .data = malloc(size * sizeof(uint8_t)),
        .size = size
    };
    memcpy(new.data, string, size);
    return new;
}

byte_array from_data(const uint8_t *data, const size_t size) {
    const byte_array new = {
        .data = malloc(size * sizeof(uint8_t)),
        .size = size
    };
    memcpy(new.data, data, size);
    return new;
}
