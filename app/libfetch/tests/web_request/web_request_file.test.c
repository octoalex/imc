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
 * Created by octoalex on 02/12/2025.
 */

#include <imc/fetch/web_request.h>
#include "common.h"

const char *const FETCH_PATH = "file_fetch.html";

int main() {
    if (!setup_web_request()) {
        fprintf(stderr, "Fetch setup has failed!\n");
        cleanup_web_request();
        return -1;
    }

    // web_request to memory
    FILE *file = fopen(FETCH_PATH, "w");

    const bool success = web_request_file(TEST_URL, file);
    cleanup_web_request();

    fclose(file);

    // reset file
    file = fopen(FETCH_PATH, "r");

    // read all
    size_t size;
    const uint8_t *data = (uint8_t *)read_all_file(file, &size);

    // close again
    fclose(file);
    file = nullptr;

    if (!success) {
        // web_request has failed, abort
        fprintf(stderr, "Fetch has failed!\n");
        return -1;
    }
    return check_downloaded_data(data, size);
}
