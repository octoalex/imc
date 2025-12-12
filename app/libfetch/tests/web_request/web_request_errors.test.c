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
 * Created by octoalex on 12/12/2025.
 */

#include <imc/fetch/web_request.h>
#include "common.h"

const char *const HTTP_URL = "http://www.example.com/";
const char *const FTP_URL = "ftp://ftp.example.com";
const char *const FILE_URL = "file://bin/bash";

const char *const BAD_URL = "https://poorly@formatted@url";
const char *const UNREACHABLE_URL = "https://non-existant.none/";
const char *const INACCESSIBLE_URL = "https://info.cern.ch/not";
const char *const NULL_HOST_URL = "https://0.0.0.0/";

bool print_and_check(const char *name, web_request_status returned, web_request_status base);

int main() {
    byte_array buffer;
    const web_request_status           https_status = web_request(TEST_URL,         &buffer, DEFAULT_TIMEOUT);
    const web_request_status            http_status = web_request(HTTP_URL,         &buffer, DEFAULT_TIMEOUT);
    const web_request_status             ftp_status = web_request(FTP_URL,          &buffer, DEFAULT_TIMEOUT);
    const web_request_status            file_status = web_request(FILE_URL,         &buffer, DEFAULT_TIMEOUT);
    const web_request_status             bad_status = web_request(BAD_URL,          &buffer, DEFAULT_TIMEOUT);
    const web_request_status     unreachable_status = web_request(UNREACHABLE_URL,  &buffer, DEFAULT_TIMEOUT);
    const web_request_status    inaccessible_status = web_request(INACCESSIBLE_URL, &buffer, DEFAULT_TIMEOUT);
    const web_request_status      impossible_status = web_request(NULL_HOST_URL,    &buffer, DEFAULT_TIMEOUT);
    free_byte_array(&buffer);

    const bool https        = print_and_check("https",               https_status, WEB_REQUEST_STATUS_OK);
    const bool http         = print_and_check("http",                 http_status, WEB_REQUEST_STATUS_OK);
    const bool ftp          = print_and_check("ftp",                   ftp_status, WEB_REQUEST_STATUS_INVALID_PROTOCOL);
    const bool file         = print_and_check("file",                 file_status, WEB_REQUEST_STATUS_INVALID_PROTOCOL);
    const bool bad          = print_and_check("bad",                   bad_status, WEB_REQUEST_STATUS_BAD_URL);
    const bool unreachable  = print_and_check("unreachable",   unreachable_status, WEB_REQUEST_STATUS_HOST_UNREACHABLE);
    const bool inaccessible = print_and_check("inaccessible", inaccessible_status, WEB_REQUEST_STATUS_DOWNLOAD_ERROR);
    const bool impossible   = print_and_check("impossible",     impossible_status, WEB_REQUEST_STATUS_CONNECT_ERROR);

    return https && http && ftp && file && bad && unreachable && inaccessible && impossible ? 0 : -1;
}

bool print_and_check(const char *name, const web_request_status returned, const web_request_status base) {
    fprintf(stderr, "%s: got %d / (expected %d)\n", name, returned, base);
    return returned == base;
}
