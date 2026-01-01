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
 * Created by octoalex on 31/12/2025.
 */

#ifndef IMC_STATUS_CODES_H
#define IMC_STATUS_CODES_H

#include <imc/common/status.h>

/// Status codes for the fetch function suite
typedef enum fetch_status_code {
    /// The operation was successful
    FETCH_STATUS_SUCCESS = STATUS_SUCCESSFUL_CODE,
    /// Downloading the resource was not possible
    FETCH_STATUS_DOWNLOAD_FAILED = 0x0000'0001,
    /// Caching the resource was not possible
    FETCH_STATUS_CACHING_FAILED = 0x0000'0002,
    /// Arguments were not properly formatted
    FETCH_STATUS_BAD_ARGUMENTS = 0x0000'0003,
    /// The downloaded file does not match the resource
    /// @note This is not triggered by an outdated cache, but if both the cache and the downloaded resource don't
    ///       match
    FETCH_STATUS_BAD_RESOURCE = 0x0000'0004
} fetch_status_code;

typedef status fetch_status;

#endif //IMC_STATUS_CODES_H
