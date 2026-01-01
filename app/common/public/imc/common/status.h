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
 * Created by octoalex on 30/12/2025.
 */

#ifndef IMC_STATUS_H
#define IMC_STATUS_H

#include <imc/common/nullable.h>

/// Unified status code structure
typedef struct status {
    /// The error code itself
    int code;
    /// Optional error message
    /// @details To not be overwritten
    char *NULLABLE message;
} status;

/// Reserved status code to indicate success
constexpr int STATUS_SUCCESSFUL_CODE = 0;
/// Reserved status code to indicate an invalid status
constexpr int STATUS_NULL_CODE = -1;

/// Checks whether the given status is successful
/// @param status The status
/// @return Whether the status is successful
bool is_status_success(status status);

/// Frees a status and sets it to a safe value
/// @param status A pointer to the status to free
void free_status(status *status);

/// Frees a status without setting it to a safe value
/// @param status The status to free
void free_status_unsafe(status status);

#endif //IMC_STATUS_H
