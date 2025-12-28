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
#include <imc/imc/launch_process.h>
#include <sys/stat.h>
#include <sys/types.h>

constexpr int BUFFER_SIZE = 16;

int main(const int argc, const char *argv[]) {
    if (argc != 1 && argc != 3) {
        fprintf(stderr, "Incorrect number of arguments! Expected 0 or 2, got %d\n", argc - 1);
        return -1;
    }

    if (argc == 1) {

        int parent_pipe[2];
        pipe(parent_pipe);

        char read_fd[BUFFER_SIZE];
        char write_fd[BUFFER_SIZE];

        sprintf(read_fd, "%d", parent_pipe[0]);
        sprintf(write_fd, "%d", parent_pipe[1]);
        // send the file descriptors, so the child can check if they're open
        const char *command[] = {
            *argv,
            read_fd,
            write_fd,
            nullptr
        };

        const pid_t process = launch_process(command, nullptr, nullptr, stdout, nullptr);

        const int exit = wait_process(process, nullptr);

        // close files for good measure
        close(parent_pipe[0]);
        close(parent_pipe[1]);

        // if the child still had those files open, exit will be true (1 in other words), so the test shall return
        // non-zero
        // if the child didn't have those files open, exit will be false (0), so the test shall return 0
        return -exit;

    } else {
        // child mode
        const int read_fd = (int)strtol(argv[1], nullptr, 10);
        const int write_fd = (int)strtol(argv[2], nullptr, 10);

        struct stat st;
        // check if either of the files are open, and return true if either is
        return fstat(read_fd, &st) != -1 || fstat(write_fd, &st) != -1;
    }
}
