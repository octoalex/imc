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
 * Created by octoalex on 23/11/2025.
 */

// This test checks if file descriptors are inherited by launched process

#include <stdlib.h>
#include <imc/libimc/launch_process.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

constexpr int BUFFER_SIZE = 16;

int main(int argc, const char *argv[]) {
    if (argc == 1) {

        int parent_pipe[2];
        pipe(parent_pipe);

        char read_fd[BUFFER_SIZE];
        char write_fd[BUFFER_SIZE];
        sprintf(read_fd, "%d", parent_pipe[0]);
        sprintf(write_fd, "%d", parent_pipe[1]);
        printf("Sending file descriptors [%d] and [%d]\n", parent_pipe[0], parent_pipe[1]);

        const char *command[] = {
            *argv,
            read_fd,
            write_fd,
            nullptr
        };

        pid_t process = launch_process(command, nullptr, nullptr, stdout, nullptr);

        int exit = wait_process(process, nullptr);

        close(parent_pipe[0]);
        close(parent_pipe[1]);

        return exit;

    } else if (argc == 3) {
        // child mode
        int read_fd = (int)strtol(argv[1], nullptr, 10);
        int write_fd = (int)strtol(argv[2], nullptr, 10);
        printf("Received file descriptors [%d] and [%d]\n", read_fd, write_fd);

        struct stat st;
        return fstat(read_fd, &st) != -1 || fstat(write_fd, &st) != -1;
    }
    return -1;
}
