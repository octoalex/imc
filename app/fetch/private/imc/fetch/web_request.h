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

#include <imc/common/byte_array.h>
#include <imc/common/status.h>
#include <imc/fetch/status_codes.h>

/// The status of the web request
typedef status web_request_status;

/// Status code enum for web_request
/// @details This was originally more complex, however, since it's an internal function, and most of the status codes
///          were translated into the generic FETCH_STATUS_DOWNLOAD_FAILED, it makes more sense to only report what's
///          useful, which can be expanded if necessary. <br/>
///          Furthermore, all the info the user cares about is encoded in the message field, so even these fields are
///          usually ignored
typedef enum web_request_status_code {
    WEB_REQUEST_STATUS_SUCCESS = FETCH_STATUS_SUCCESS,
    // Codes match, this may change in the future
    WEB_REQUEST_STATUS_UNSUPPORTED_PROTOCOL = FETCH_STATUS_BAD_ARGUMENTS,
    WEB_REQUEST_STATUS_BAD_URL = FETCH_STATUS_BAD_ARGUMENTS,
    WEB_REQUEST_STATUS_FAILED = FETCH_STATUS_DOWNLOAD_FAILED
} web_request_status_code;

/// Default timeout for @link web_request @endlink
constexpr unsigned long DEFAULT_TIMEOUT = 300'000;

/// Gets a file from a url to memory
/// @param url The url to download
/// @param buffer Pointer to where the downloaded data will be put
/// @param timeout Maximum number of milliseconds the web request can take <br/>
///                If set to `0`, the default value will be used <br/>
///                If set to `< 0`, no timeout will be set
/// @note Supports only HTTP and HTTPS
/// @return The web request's status code
web_request_status *web_request(const char *url, byte_array *buffer, unsigned long timeout);

/// Performs necessary cleanup operations for web_request
/// @note To be performed <b>only</b> after the last web request
void cleanup_web_request();

#endif //IMC_WEB_REQUEST_H
