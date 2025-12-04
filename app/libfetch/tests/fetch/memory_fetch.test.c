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

#include <imc/fetch/fetch.h>
#include "fetch_common.h"

int main() {
    if (!setup_fetch()) {
        fprintf(stderr, "Fetch setup has failed!\n");
        cleanup_fetch();
        return -1;
    }

    // fetch to memory
    uint8_t *data;
    size_t size;

    const bool success = fetch(TEST_URL, &data, &size);
    cleanup_fetch();

    if (!success) {
        // fetch has failed, abort
        fprintf(stderr, "Fetch has failed!\n");
        return -1;
    }

    return check_downloaded_data(data, size);
}