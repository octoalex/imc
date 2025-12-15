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
 * Created by octoalex on 22/11/2025.
 */

#include <stdlib.h>
#include <time.h>
#include <imc/libimc/launch_process.h>
#include <imc/common/pipe.h>

// simple strings
const char *const IN_STRING = "This is an input";
const char *const OUT_STRING = "This is an output";
const char *const ERR_STRING = "This is an error";

// by using a fixed size number, conversion to string won't cause any problems
constexpr int RANDOM_MAX_VALUE = 999;
constexpr int RANDOM_MIN_VALUE = 100;

constexpr size_t IO_BUFFER_SIZE = 32;

int main(const int argc, const char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Incorrect number of arguments! Expected 0 or 1, got %d\n", argc - 1);
        return -1;
    }

    if (argc == 1) {
        // parent mode

        // in files
        FILE *in_child;
        FILE *in_parent;
        if (!create_pipe(&in_child, &in_parent)) {
            fprintf(stderr, "Failure to create input pipe!\n");
            return -1;
        }

        // out files
        FILE *out_child;
        FILE *out_parent;
        if (!create_pipe(&out_parent, &out_child)) {
            fprintf(stderr, "Failure to create output pipe!\n");
            return -1;
        }

        // err files
        FILE *err_child;
        FILE *err_parent;
        if (!create_pipe(&err_parent, &err_child)) {
            fprintf(stderr, "Failure to error output pipe!\n");
            return -1;
        }

        // Here's the fix discussed later down
        // by default, it seems like the file is opened in full buffer mode (unclear why), so it has to be manually set
        // here to buffer by line
        char *buffer = calloc(IO_BUFFER_SIZE, sizeof(char));
        setvbuf(in_parent, buffer, _IOLBF, IO_BUFFER_SIZE);

        // generation of 2 randoms
        // srand will do, there's no issue with using a low security random, because this isn't tied to security
        srand(time(nullptr));
        const int random1 = rand() % (RANDOM_MAX_VALUE - RANDOM_MIN_VALUE + 1) + RANDOM_MIN_VALUE;
        const int random2 = rand() % (RANDOM_MAX_VALUE - RANDOM_MIN_VALUE + 1) + RANDOM_MIN_VALUE;

        char random1_string[4] = { };
        sprintf(random1_string, "%d", random1);

        const char *command[] = {
            *argv,
            random1_string,
            nullptr
        };

        const pid_t process = launch_process(command, nullptr, in_child, out_child, err_child);

        // now that we've passed the files to the child process, they can be closed
        fclose(in_child);
        fclose(out_child);
        fclose(err_child);

        // 1. simulate input
        fprintf(in_parent, "%d\n\n", random2);
        // FIXED: issue caused because standard file buffering behavior was full instead of line

        // 2. get that input echoed back
        int echoed;
        fscanf(out_parent, "%d", &echoed);

        // 3. now, read the error, which will be the argument
        int errored;
        fscanf(err_parent, "%d", &errored);

        // wait for the child to terminate
        bool was_killed;
        wait_process(process, &was_killed);

        free(buffer);
        // setting to null for good practice
        buffer = nullptr;

        if (was_killed) {
            fprintf(stderr, "Child was killed!\n");
            return -1;
        } else if (random2 != echoed) {
            fprintf(stderr, "In-Out Transmission failed! Sent %d, received %d!\n", random2, echoed);
            return -1;
        } else if (random1 != errored) {
            fprintf(stderr, "Argument-Error Transmission failed! Sent %d, received %d\n", random1, errored);
            return -1;
        }
        // success!
        return 0;
    } else if (argc == 2) {
        // child mode

        // 1. read input
        int to_echo;
        scanf("%d", &to_echo);

        // 2. echo input back
        printf("%d\n", to_echo);

        // 3. write argument as error
        fprintf(stderr, "%s\n", argv[1]);

        // done, return 0
        return 0;
    }
}
