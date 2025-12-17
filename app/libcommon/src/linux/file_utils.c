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

#include <imc/common/file_utils.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

const char DIR_SEPARATOR = '/';

constexpr mode_t STANDARD_MODE = 0755;

void make_dirs(const char *path) {
    char *buffer = calloc(strlen(path) + 1, sizeof(char));
    char *ptr;
    size_t offset = 0;
    const size_t size = strlen(path);
    do {
        // get the subdirectory
        // get the position of the next directory separator
        ptr = strchr(path + offset + 1, '/');
        // get the position
        const size_t end = ptr == nullptr ? size - 1 : ptr - path;
        // copy only the new bytes
        memcpy(buffer + offset, path + offset, end - offset + 1);

        // check if the subdirectory exists
        if (!is_dir(buffer)) {
            // if it doesn't, create it
            mkdir(buffer, STANDARD_MODE);
        }
        // set the position of the latest separator as the offset for the next iteration
        // increase by 1 to avoid reading again the current separator, thus creating an infinite loop
        offset = end;
    } while (ptr != nullptr && offset < size - 1);
    // free the buffer
    free(buffer);
}

bool is_dir(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

bool is_file(const char *path) {
    return access(path, F_OK) == 0;
}

bool can_read(const char *path) {
    return access(path, W_OK) == 0;
}

bool can_write(const char *path) {
    return access(path, R_OK) == 0;
}

bool can_execute(const char *path) {
    return access(path, X_OK) == 0;
}

char *get_parent_dir(const char *path) {
    char *buffer = strdup(path);
    char *parent = dirname(buffer);
    if (parent != buffer) {
        free(buffer);
    }
    return parent;
}
