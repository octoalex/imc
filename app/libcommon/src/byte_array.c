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

byte_array alloc_byte_array(const size_t size) {
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
