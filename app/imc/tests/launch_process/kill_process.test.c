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

#include <limits.h>
#include <signal.h>
#include <imc/imc/launch_process.h>

int main(const int argc, const char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Incorrect number of arguments! Expected 0 or 1, got %d\n", argc - 1);
        return -1;
    }

    if (argc == 1) {
        // parent mode
        const char *command[] = {
            *argv,
            "go to sleep",
            nullptr
        };

        const pid_t process = launch_process(command, nullptr, nullptr, nullptr, nullptr);

        // time to die
        const bool murder_successful = kill_process(process);

        // check also if wait_process behaves as expected
        bool was_killed;
        const int signal = wait_process(process, &was_killed);

        // final checks
        if (!murder_successful) {
            fprintf(stderr, "kill_process failed!\n");
            return -1;
        } else if (!was_killed) {
            fprintf(stderr, "wait_process failed to recognize that the process was killed!\n");
            return -1;
        } else if (signal != SIGINT) {
            fprintf(stderr, "Process was killed for reasons other than interruption. Expected: %d, found %d\n",
                SIGINT, signal);
            fprintf(stderr, "\tTest status unclear, thus failing!\n");
            return -1;
        }
        return 0;
    } else {
        // ah, what a wonderful day to be alive
        // I'll go to sleep for a bit, and then wake up to be alive again
        usleep(UINT_MAX);
        return 0;
    }
}
