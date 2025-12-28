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

#include <stdio.h>
#include <string.h>
#include <imc/common/file_utils.h>

const char *const PATH_SHORT = "a/b/c/d";
const char *const PATH_LONG = "e/f/g/h/";

int main() {
    make_dirs(PATH_SHORT);
    make_dirs(PATH_LONG);
    const bool short_passed = is_dir(PATH_SHORT);
    const bool long_passed = is_dir(PATH_LONG);
    if (!short_passed) {
        fprintf(stderr, "make_dirs failed with path not terminated by separator (/)!\n");
    }
    if (!long_passed) {
        fprintf(stderr, "make_dirs failed with path terminated by separator (/)!\n");
    }
    return short_passed && long_passed ? 0 : -1;
}
