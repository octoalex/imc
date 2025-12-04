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

/// Fetches a file with a url
/// @param url The url to download
/// @param data Pointer to where the data array will be put
/// @param size Pointer to where the array's size will be put
/// @return Whether the fetch was successful
bool fetch(const char *url, uint8_t **data, size_t *size);

/// Fetches a file with a url
/// @param url The url to download
/// @param file File where the data will be saved to
/// @return Whether the fetch was successful
bool fetch_file(const char *url, FILE *file);

/// Performs necessary setup operations for fetch
/// @return Whether the setup was successful
bool setup_fetch();

/// Performs necessary cleanup operations for fetch
/// @note To be performed <b>only</b> after the last fetch
void cleanup_fetch();

#endif //IMC_FETCH_H