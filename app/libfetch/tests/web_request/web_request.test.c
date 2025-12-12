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
#include <stdlib.h>
#include "common.h"

int main() {
    byte_array buffer;

    const web_request_status status = web_request(TEST_URL, &buffer, DEFAULT_TIMEOUT);
    cleanup_web_request();

    if (status == WEB_REQUEST_STATUS_SETUP_ERROR) {
        fprintf(stderr, "Web Request setup has failed!\n");
        return -1;
    } else if (status != WEB_REQUEST_STATUS_OK) {
        // web_request has failed, abort
        fprintf(stderr, "Web Request has failed!\n");
        return -1;
    }

    const int result = check_downloaded_data(buffer.data, buffer.size);
    free_byte_array(&buffer);
    return result;
}