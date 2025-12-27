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
 * Created by octoalex on 26/12/2025.
 */

#include <stdio.h>
#include "paths.test.h"
#include "../common.test.h"

int main() {
    FILE *file = fopen(CURL_FILE_PATH, "r");
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fclose(file);
    file = fopen(SIZE_FILE_PATH, "w");
    fprintf(file, "%lu\n", size);
    fclose(file);
    return 0;
}
