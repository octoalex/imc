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
 * Created by octoalex on 28/11/2025.
 */

#ifndef IMC_WEB_REQUEST_H
#define IMC_WEB_REQUEST_H

#include <stdio.h>
#include <stdint.h>
#include <imc/common/byte_array.h>

typedef enum web_request_status : uint8_t {
    /// Download went successfully
    WEB_REQUEST_STATUS_OK,
    /// Setup was unsuccessful
    WEB_REQUEST_STATUS_SETUP_ERROR,
    /// URL was improperly formatted
    WEB_REQUEST_STATUS_BAD_URL,
    /// Request was not http or https
    WEB_REQUEST_STATUS_INVALID_PROTOCOL,
    /// Host could not be reached
    WEB_REQUEST_STATUS_HOST_UNREACHABLE,
    /// Connection to the host failed
    WEB_REQUEST_STATUS_CONNECT_ERROR,
    /// Downloading the file failed
    WEB_REQUEST_STATUS_DOWNLOAD_ERROR,
    /// Download took too long
    WEB_REQUEST_STATUS_TIMEOUT,
    /// There was insufficient memory to download the file
    /// @note This is catastrophic
    WEB_REQUEST_STATUS_OUT_OF_MEMORY,
    /// Catch-all error for errors that shouldn't happen
    WEB_REQUEST_STATUS_OTHER
} web_request_status;

constexpr unsigned long DEFAULT_TIMEOUT = 300'000;

/// Gets a file from a url to memory
/// @param url The url to download
/// @param buffer Pointer to where the downloaded data will be put
/// @param timeout Maximum number of milliseconds the web request can take <br/>
///                If set to 0, no timeout will be set
///                If set to < 0, the default value will be used
/// @return The web request's status code
web_request_status web_request(const char *url, byte_array *buffer, unsigned long timeout);

/// Performs necessary cleanup operations for web_request
/// @note To be performed <b>only</b> after the last web request
void cleanup_web_request();

#endif //IMC_WEB_REQUEST_H