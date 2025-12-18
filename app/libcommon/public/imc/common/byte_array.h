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
#include <imc/common/nullable.h>

/// An array of bytes
/// @note It is recommended to allocate it with @code alloc_byte_array(size_t)@endcode and to deallocate it with
///       @code free_byte_array(byte_array *)@endcode <br/>
/// @details To allocate, deallocate, resize and copy manually, see the aforementioned functions' implementation details
typedef struct byte_array {
    /// The bytes
    uint8_t *NULLABLE data;
    /// The number of bytes
    size_t size;
} byte_array;

/// Allocates a zeroed byte array
/// @param size The size of the array
/// @return The array
/// @note Setting @code size@endcode to @code 0@endcode will return an empty array
/// @details Functionally, it's just a @code calloc@endcode call, however it ensures that size is identical to the
///          actual size of the array, and simplifies creation (1 line instead of 4)
byte_array alloc_byte_array(size_t size);

/// Deallocates a byte array
/// @param array The array
/// @details This function does 2 things: it calls @code free@endcode to deallocate @code data@endcode, and then
///          replaces @code data@endcode and @code size@endcode with @code nullptr@endcode and @code 0@endcode
///          respectively, to clearly mark the array as deallocated, to allow recycling it, and so if it's accidentally
///          passed to some function, it will not cause any illegal memory accesses
void free_byte_array(byte_array *array);

/// Resize a byte array
/// @param array The array to resize
/// @param new_size The size to resize the array to
/// @note New bytes are zeroed
/// @details This function does 2 things: it calls @code realloc@endcode to deallocate the data, and then replaces size
///          with the new size, to ensure @code size@endcode is always the same as the real size, and simplifying
///          resizing it
void resize_byte_array(byte_array *array, size_t new_size);

/// Copy a byte array
/// @param base The array to copy
/// @return A copied array
/// @details This function calls @code malloc@endcode to allocate a new array of @code base.size@endcode bytes, then
///          calls @code memcpy@endcode to copy the bytes over.
byte_array copy_byte_array(const byte_array *base);

/// Creates a byte array from a C (null terminated) string
/// @param string The C (null terminated) string
/// @return A byte array with a copy of the string
byte_array from_c_string(const char *string);

/// Creates a byte array from an array of bytes and an associated size
/// @param data The array of bytes
/// @param size The associated size of the array of bytes
/// @returns A byte array with a copy of the given data
byte_array from_data(const uint8_t *data, size_t size);

#endif //IMC_BYTE_ARRAY_H