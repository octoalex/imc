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
 * Created by octoalex on 22/12/2025.
 */

#ifndef IMC_RESOURCE_H
#define IMC_RESOURCE_H

#include <imc/common/nullable.h>
#include <imc/fetch/hash.h>

/// Locations and metadata of a file
typedef struct resource {
    /// The hash of the file
    hash hash;
    /// The URL of the file
    const char *url;
    /// The location where the file will be saved locally
    const char *NULLABLE path;
    /// The size of the file
    size_t size;
} resource;

#endif //IMC_RESOURCE_H
