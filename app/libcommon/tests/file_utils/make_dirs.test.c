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

const char *const MODE_USE = "use";
const char *const MODE_TEST = "test";
const char *const PATH = "a/b/c/d";

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Expected 1 argument, got %d instead!\n", argc - 1);
        return -1;
    }
    const char *mode = argv[1];
    if (strcmp(mode, MODE_USE) == 0) {
        make_dirs(PATH);
        return 0;
    } else if (strcmp(mode, MODE_TEST) == 0) {
        return is_dir(PATH);
    }
    fprintf(stderr, "Unknown mode %s\n", mode);
    return -1;
}
