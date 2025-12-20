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

/// The status of the web request
typedef struct web_request_status {
    /// Simple status codes describing how the operation went
    enum {
        /// The request was successful
        WEB_REQUEST_STATUS_SUCCESS,
        /// The protocol was not HTTP or HTTPS
        WEB_REQUEST_STATUS_UNSUPPORTED_PROTOCOL,
        /// The url was poorly formatted
        WEB_REQUEST_STATUS_BAD_URL,
        /// The setup failed
        /// @note For more information, see @link code@endlink
        WEB_REQUEST_STATUS_SETUP_FAILED,
        /// The download failed
        /// @note For more information, see @link code@endlink
        WEB_REQUEST_STATUS_FAILED,
        /// The function ran out of memory while downloading the file
        /// @note This is catastrophic
        WEB_REQUEST_STATUS_OUT_OF_MEMORY
    } status;
    /// Implementation defined error code
    int code;
    /// If the underlying implementation allows for a human-readable error description, it can be found here
    /// @note @code free()@endcode must be manually called on it
    const char *message;
} web_request_status;

/// Default timeout for @link web_request@endlink
constexpr unsigned long DEFAULT_TIMEOUT = 300'000;

/// Gets a file from a url to memory
/// @param url The url to download
/// @param buffer Pointer to where the downloaded data will be put
/// @param timeout Maximum number of milliseconds the web request can take <br/>
///                If set to 0, the default value will be used
///                If set to < 0, no timeout will be set
/// @note Supports only HTTP and HTTPS
/// @return The web request's status code
web_request_status web_request(const char *url, byte_array *buffer, unsigned long timeout);

/// Performs necessary cleanup operations for web_request
/// @note To be performed <b>only</b> after the last web request
void cleanup_web_request();

#endif //IMC_WEB_REQUEST_H
