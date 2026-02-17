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

#ifndef IMC_FETCH_H
#define IMC_FETCH_H

#include <imc/common/nullable.h>
#include <imc/common/byte_array.h>
#include <imc/fetch/resource.h>
#include <json.h>
#include <stdio.h>
#include <imc/fetch/status_codes.h>

/// Downloads a file off of the internet and caches it, or gets it from the cache, and returns it as a byte array
/// @param resource The locations and metadata of the file to fetch
/// @param bytes Nullable pointer to a byte array, where the downloaded data will also be put <br/>
///              May only be null if the resource's path is not null
/// @return The status of the operation
/// @note Currently, the only supported protocols are HTTP and HTTPS
fetch_status fetch(const resource *resource, byte_array *NULLABLE bytes);

/// Downloads a file off of the internet and caches it, or gets it from the cache, and returns it as a JSON object
/// @param resource The locations and metadata of the file to fetch
/// @param json Nullable pointer to a JSON object, where the downloaded data will also be put, after being parsed as a
///             JSON document <br/>
///             If the parsing operation fails, the pointer will be left to null <br/>
///             May only be null if the resource's path is not null
/// @return The status of the operation
/// @note Currently, the only supported protocols are HTTP and HTTPS
fetch_status fetch_json(const resource *resource, json_object *NULLABLE *json);

/// Downloads a file off of the internet and caches it, or gets it from the cache, and returns it as a file
/// @param resource The locations and metadata of the file to fetch
/// @param file Nullable pointer to a file, where the downloaded data will also be put, as a readable file pointer <br/>
///             May only be null if the resource's path is not null
/// @return The status of the operation
/// @note Currently, the only supported protocols are HTTP and HTTPS
fetch_status fetch_file(const resource *resource, FILE *NULLABLE *file);

#endif //IMC_FETCH_H
