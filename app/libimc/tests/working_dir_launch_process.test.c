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
 * Created by octoalex on 25/11/2025.
 */

#include <stdlib.h>
#include <string.h>
#include <imc/libimc/launch_process.h>
#include <linux/limits.h>

int main(const int argc, const char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Incorrect number of arguments! Expected 0 or 1, got %d\n", argc - 1);
        exit(-1);
    }

    if (argc == 2) {
        // parent mode
        // the argument is the source dir, to which the child process will be launched in

        const char *command[] = {
            *argv,
            nullptr
        };

        // the child process will communicate its current folder through a pipe

        int wd_pipe[2];
        pipe(wd_pipe);

        FILE *out = fdopen(wd_pipe[1], "w");
        FILE *in = fdopen(wd_pipe[0], "r");

        const pid_t process = launch_process(command, argv[1], nullptr, out, nullptr);

        if (process == PROCESS_ERROR_WORKING_DIRECTORY_INVALID) {
            fprintf(stderr, "Directory \"%s\" either does not exist, or is not accessible!\n", argv[1]);
            exit(-1);
        }

        // for good practice, the end of the pipe that we don't need should be closed
        fclose(out);

        // now, prepare a buffer, and read from the pipe
        char received_wd[strlen(argv[1]) + 1];
        fscanf(in, "%s", received_wd);

        // wait for the program to terminate
        bool was_killed;
        wait_process(process, &was_killed);

        // now, do the tests!
        if (was_killed) {
            fprintf(stderr, "Child was killed!\n");
            return -1;
        } else if (strcmp(argv[1], received_wd) != 0) {
            fprintf(stderr,
                "Process expected to be launched in directory \"%s\", but was launched in directory \"%s\"!\n",
                argv[1], received_wd);
            return -1;
        }
        return 0;
    } else {
        char *current_wd = calloc(PATH_MAX, sizeof(char));
        getcwd(current_wd, PATH_MAX);

        printf("%s\n", current_wd);

        free(current_wd);

        return 0;
    }
}
