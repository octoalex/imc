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
    /// Whether it was created by @link create_status @endlink
    /// @note If manually initializing, please set to false
    bool allocated_at_runtime;
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

/// Simple status to be used when the program runs out of memory
extern const status STATUS_ERROR_OUT_OF_MEMORY;
/// Status template to be used when a file is not found
/// @note Format with
///       @code
///       // - 2 (for %s) + 1 (for the null terminator) = - 1
///       char *message = malloc(strlen(STATUS_ERROR_FILE_NOT_FOUND.message) + strlen(filename) - 1);
///       sprintf(message, STATUS_ERROR_FILE_NOT_FOUND.message, filename);
///       status s = {
///           .code = STATUS_ERROR_FILE_NOT_FOUND.code,
///           .message = message
///       };
///       @endcode
///       where `filename` is the name of the file, and `s` is the status
extern const status STATUS_ERROR_FILE_NOT_FOUND;

/// Checks whether the given status is successful
/// @param status The status
/// @return Whether the status is successful
bool is_status_success(const status *status);

/// Creates a status object
/// @param code The code of the status
/// @param format The message of the status (formatted as a printf format string)
/// @param ... The format arguments
/// @return The pointer to the created status object
status *create_status(int code, const char *NULLABLE format, ...);

/// Frees a status and sets it to a safe value
/// @param status A pointer to the status to free
void free_status(status *status);

/// Frees a status without setting it to a safe value
/// @param status The status to free
void free_status_unsafe(status status);

/// Exits the program with the given status code and error message if the status code is non-zero
/// @param status The status code
void error(const status *status);

/// Prints a warning to the standard error, and continues to run the program if the status code is non-zero
/// @param status The status code
void warn(const status *status);

#endif //IMC_STATUS_H
