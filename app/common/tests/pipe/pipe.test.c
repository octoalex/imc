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
 * Created by octoalex on 15/12/2025.
 */

#include <imc/common/pipe.h>
#include <string.h>

const char *const STRING = "Hello, I am a string, and I like goth men, women and non-binary people";

int main() {
    const size_t string_size = strlen(STRING);
    FILE *read;
    FILE *write;
    if (!create_pipe(&read, &write)) {
        fprintf(stderr, "Pipe creation failed!\n");
        return -1;
    }

    fwrite(STRING, sizeof(char), string_size, write);
    fclose(write);

    char buffer[string_size + 1];
    fread(buffer, sizeof(char), string_size + 1, read);
    fclose(read);

    const bool equal = strcmp(STRING, buffer) == 0;

    if (!equal) {
        fprintf(stderr, "Transmission through the pipe failed!\n");
        return -1;
    }
}
