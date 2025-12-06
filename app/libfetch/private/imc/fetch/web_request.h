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

#ifndef IMC_FETCH_H
#define IMC_FETCH_H

#include <stdio.h>
#include <stdint.h>

/// Buffer where downloaded data will be put
typedef struct web_request_buffer {
    /// The actual data
    /// @note Must be manually deallocated with @code free()@endcode from @headerfile stdlib.h
    const uint8_t *data;
    /// The size of @code data@endcode
    size_t size;
} web_request_buffer;

/// Gets a file from a url to memory
/// @param url The url to download
/// @param buffer Pointer to where the downloaded data will be put
/// @return Whether the web request was successful
bool web_request_memory(const char *url, web_request_buffer *buffer);

/// Gets a file from a url to another file
/// @param url The url to download
/// @param file File where the data will be saved to
/// @return Whether the web request was successful
bool web_request_file(const char *url, FILE *file);

/// Performs necessary setup operations for web_request
/// @return Whether the setup was successful
bool setup_web_request();

/// Performs necessary cleanup operations for web_request
/// @note To be performed <b>only</b> after the last web request
void cleanup_web_request();

#endif //IMC_FETCH_H