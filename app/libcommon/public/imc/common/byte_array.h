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

#ifndef IMC_BYTE_ARRAY_H
#define IMC_BYTE_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct byte_array {
    uint8_t *data;
    size_t size;
} byte_array;

byte_array alloc_byte_array(size_t size);

void free_byte_array(byte_array *array);

#endif //IMC_BYTE_ARRAY_H