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
 * Created by octoalex on 11/12/2025.
 */

#ifndef IMC_FILE_UTILS_H
#define IMC_FILE_UTILS_H

extern const char DIR_SEPARATOR;

/// Create a series of nested directories
/// @param path All the directories to create
void make_dirs(const char *path);

/// Checks if a path exists and is a directory
/// @param path The directory to check
/// @return Whether the path exists and is a directory
bool is_dir(const char *path);

/// Checks if a path exists and is a file
/// @param path The file to check
/// @return Whether the path exists and is a file
bool is_file(const char *path);

/// Checks if a path exists, is a file and can be read
/// @param path The file to check
/// @return Whether the file can be read
bool can_read(const char *path);

/// Checks if a path exists, is a file and can be written to
/// @param path The file to check
/// @return Whether the file can be written to
bool can_write(const char *path);

/// Checks if a path exists, is a file and can be executed
/// @param path The file to check
/// @return Whether the file can be executed
bool can_execute(const char *path);

/// Gets the parent directory of the given path, or an empty string if the path points to the root
/// @param path The path from where the parent directory will be found
/// @return The parent directory's path <br/>
///         This path will never terminate with /, unless it's the root directory
///         The string must be manually freed
char *get_parent_dir(const char *path);

/// Removes useless and/or redundant elements from a path.
/// @details Simple @code .@endcode directories are removed (for example, @code a/./b@endcode becomes
///          @code a/b@endcode), and "up" nodes such as @code ..@endcode eliminate the previous directory, unless there
///          is nothing to be eliminated (for example, @code a/../b@endcode becomes @code b@endcode)
/// @param path The path
/// @return The cleaned up path, never with a trailing @code /@endcode
/// @note Returned path must be manually freed
char *clean_path(const char *path);

/// Gets the timestamp of when the file was last modified
/// @param path The path of the file
/// @return The timestamp
struct timespec get_modified_timestamp(const char *path);

/// Gets the timestamp of when the file was last accessed
/// @param path The path of the file
/// @return The timestamp
struct timespec get_access_timestamp(const char *path);

#endif //IMC_FILE_UTILS_H
