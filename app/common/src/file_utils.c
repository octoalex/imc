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
 * Created by octoalex on 18/12/2025.
 */

#include <imc/common/file_utils.h>
#include <string.h>
#include <stdlib.h>

const char *const PATH_UP = "..";
const char *const PATH_SELF = ".";

static char *get_part(const char *path, size_t *base) {
    const char *ptr = strchr(path + *base, DIR_SEPARATOR);
    const size_t position = ptr != nullptr ? ptr - path : strlen(path);
    char *part = calloc(position - *base + 1, sizeof(char));
    memcpy(part, path + *base, position - *base);
    *base = position + 1;
    return part;
}

static void add_part(char* cleaned, size_t *insertion, const char* part) {
    // add the part to the buffer
    if (*insertion != 0 && (*insertion != 1 || cleaned[0] != DIR_SEPARATOR)) {
        cleaned[(*insertion)++] = DIR_SEPARATOR;
    }
    strcpy(cleaned + *insertion, part);
    *insertion += strlen(part);
}

static void trim(char **ptr) {
    char *new = realloc(*ptr, strlen(*ptr) + 1);
    if (new != nullptr) {
        *ptr = new;
    }
}

char *clean_path(const char *path) {
    const size_t size = strlen(path);
    char *cleaned = calloc(sizeof(char), size);
    const bool absolute = path[0] == DIR_SEPARATOR;
    size_t insertion = absolute;
    if (absolute) {
        cleaned[0] = DIR_SEPARATOR;
    }
    size_t offset = absolute;
    do {
        char *part = get_part(path, &offset);
        if (strcmp(part, PATH_UP) == 0) {
            // most complex case

            // since all removable .. parts are guaranteed to have been removed up to this point, then if the last part
            // is an .. part, it must be because all parts in the cleared path are ..

            char *last = strrchr(cleaned, DIR_SEPARATOR);

            const bool shift = last != nullptr || absolute;
            size_t no = shift;
            // proper last part getter
            char *cleaned_part = get_part(last != nullptr ? last : cleaned, &no);

            if (strcmp(cleaned_part, PATH_UP) == 0 || strlen(cleaned) == absolute) {
                // add the part to the buffer
                add_part(cleaned, &insertion, part);
            } else if (last != nullptr) {
                last[absolute && last == cleaned] = '\0';
                insertion -= strlen(cleaned_part) + (last != cleaned);
            } else {
                cleaned[absolute] = '\0';
                insertion = absolute;
            }

            free(cleaned_part);
        } else if (strcmp(part, PATH_SELF) != 0) {
            add_part(cleaned, &insertion, part);
        }
        free(part);
    } while (offset < size);
    if (strlen(cleaned) == 0) {
        strcpy(cleaned, PATH_SELF);
    }
    trim(&cleaned);
    return cleaned;
}

char *get_parent_dir(const char *path) {
    // clean the path
    char *parent = clean_path(path);
    char *separator = strrchr(parent, DIR_SEPARATOR);
    if (separator != nullptr && separator != parent) {
        size_t no = 1;
        char *part = get_part(separator, &no);
        if (strcmp(part, PATH_UP) == 0) {
            char *extended = realloc(parent, strlen(parent) + 4);
            if (extended == nullptr) {
                free(part);
                free(parent);
                return nullptr;
            }
            parent = extended;
            parent[strlen(parent)] = DIR_SEPARATOR;
            strcpy(parent + strlen(parent), PATH_UP);
        } else {
            *separator = '\0';
        }
        free(part);
    } else {
        const bool absolute = parent[0] == DIR_SEPARATOR;
        const bool up = parent[0] == '.' == !absolute && strlen(parent) == 1;
        const bool upper = strcmp(parent + absolute, PATH_UP) == 0;
        if (up) {
            strcpy(parent + absolute, PATH_UP);
        } else if (upper) {
            strcpy(parent + absolute, PATH_UP);
            parent[absolute + 2] = DIR_SEPARATOR;
            strcpy(parent + absolute + 3, PATH_UP);
        } else if (!absolute) {
            strcpy(parent, PATH_SELF);
        }
    }
    trim(&parent);
    return parent;
}
