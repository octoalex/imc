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
#include <imc/imc/launch_process.h>

constexpr int RANDOM_MAX_VALUE = 99;
constexpr int RANDOM_MIN_VALUE = 10;

int main(const int argc, const char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Incorrect number of arguments! Expected 0 or 1, got %d\n", argc - 1);
        return -1;
    }

    if (argc == 1) {
        // parent mode
        // preparing random specific value
        srand(time(nullptr));
        const int random = rand() % (RANDOM_MAX_VALUE - RANDOM_MIN_VALUE + 1) + RANDOM_MIN_VALUE;

        char random_string[3] = { };
        sprintf(random_string, "%u", random);

        const char *command[] = {
            *argv,
            random_string,
            nullptr
        };

        // launch process in the simplest way
        const pid_t process = launch_process(command, nullptr, nullptr, nullptr, nullptr);

        // wait for the process now
        bool was_killed;
        const int exit_code = wait_process(process, &was_killed);

        return !was_killed && exit_code == random ? 0 : -1;
    } else {
        const int random = (int) strtol(argv[1], nullptr, 10);
        return random;
    }
}
