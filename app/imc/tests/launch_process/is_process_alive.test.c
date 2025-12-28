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

#include <imc/imc/launch_process.h>

int main(const int argc, const char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Incorrect number of arguments! Expected 0, got %d\n", argc - 1);
        return -1;
    }

    if (argc == 1) {
        // parent mode
        const char *command[] = {
            *argv,
            // dummy necessary to trigger child mode
            "dummy argument",
            nullptr
        };

        const pid_t process = launch_process(command, nullptr, nullptr, nullptr, nullptr);

        const bool alive = is_process_alive(process);

        // wait for process natural termination
        bool was_killed;
        wait_process(process, &was_killed);

        if (was_killed) {
            fprintf(stderr, "Child was killed!\n");
            return -1;
        }

        const bool dead = is_process_alive(process);

        // check that when the child was supposed to be alive, it was, and then when it was supposed to be dead, it was
        return alive && !dead ? 0 : -1;
    } else {
        return 0;
    }
}
