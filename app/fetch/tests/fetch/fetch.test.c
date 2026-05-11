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
 * Created by octoalex on 26/12/2025.
 */

#include <string.h>
#include <imc/fetch/fetch.h>
#include "paths.test.h"
#include "../common.test.h"
#include <imc/common/file_utils.h>
#include <sys/stat.h>
#include <sys/types.h>

static hash hash_from_file();
static size_t size_from_file();

#define HEX(c) (c >= '0' && c <= '9' ? c - '0' : (c >= 'a' && c <= 'z' ? c - 'a' : c - 'A') + 10)

const char *const CHECK_FOR_DOWNLOAD = "download";
const char *const CHECK_FOR_CACHED = "cached";

int main(const int argc, const char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Test ran with wrong number of arguments! Expected 1, got %d\n", argc - 1);
        return -1;
    } else if (strcmp(argv[1], CHECK_FOR_DOWNLOAD) != 0 && strcmp(argv[1], CHECK_FOR_CACHED) != 0) {
        fprintf(stderr, "Test mode is expected to be either \"%s\" or \"%s\", got \"%s\"!\n",
            CHECK_FOR_DOWNLOAD, CHECK_FOR_CACHED, argv[1]);
        return -1;
    }

    const bool pre_exists = is_file(CACHE_FILE_PATH);
    const struct timespec pre_modified = get_modified_timestamp(CACHE_FILE_PATH);

    const resource resource = {
        .hash = hash_from_file(),
        .url = TEST_URL,
        .path = CACHE_FILE_PATH,
        .size = size_from_file()
    };

    fetch_status *status = fetch(&resource, nullptr);

    const bool post_exists = is_file(CACHE_FILE_PATH);
    const struct timespec post_modified = get_modified_timestamp(CACHE_FILE_PATH);

    switch (status->code) {
    case FETCH_STATUS_DOWNLOAD_FAILED:
        fprintf(stderr, "FETCH_STATUS_DOWNLOAD_FAILED\n");
        break;
    case FETCH_STATUS_CACHING_FAILED:
        fprintf(stderr, "FETCH_STATUS_CACHING_FAILED\n");
        break;
    case FETCH_STATUS_BAD_ARGUMENTS:
        fprintf(stderr, "FETCH_STATUS_BAD_ARGUMENTS\n");
        break;
    case FETCH_STATUS_BAD_RESOURCE:
        fprintf(stderr, "FETCH_STATUS_BAD_RESOURCE\n");
        break;
    default:
    }
    if (status->message != nullptr) {
        fprintf(stderr, "%s\n", status->message);
    }
    const bool was_successful = status->code == FETCH_STATUS_SUCCESS;
    free_status(status);

    bool any = false;

    if (strcmp(CHECK_FOR_DOWNLOAD, argv[1]) == 0) {
        if (pre_exists) {
            fprintf(stderr, "Cache already existed when it shouldn't, run the test again\n");
            any = true;
        }
        if (!post_exists) {
            fprintf(stderr, "Saving to cache failed!\n");
            any = true;
        }
    } else {
        if (!pre_exists) {
            fprintf(stderr, "Either caching has failed in the previous test, or it was deleted in the meantime! "
                "Please run again the tests, including fetch_download too\n");
            any = true;
        }
        if (!post_exists) {
            fprintf(stderr, "Cache was deleted during fetch phase, or was initially unavailable and downloading "
                "failed too!\n");
            any = true;
        }
        if (pre_modified.tv_sec != post_modified.tv_sec || pre_modified.tv_nsec != post_modified.tv_nsec) {
            fprintf(stderr, "Cache timestamps do not match, indicating file was downloaded again!\n");
            any = true;
        }
    }

    // return -1 - any;
    return was_successful && !any ? 0 : -1;
}

static hash hash_from_file() {
    FILE *file = fopen(HASH_FILE_PATH, "r");
    char *string = nullptr;
    size_t n = 0;
    getdelim(&string, &n, EOF, file);
    fclose(file);

    size_t pos;
    for (pos = 0; pos < n; ++pos) {
        if (string[pos] == ' ') {
            break;
        }
    }
    ++pos;

    const byte_array bytes = alloc_byte_array(256 / 8);
    for (size_t i = 0; string[pos] != '\n'; pos += 2, ++i) {
        const uint8_t byte = HEX(string[pos]) << 4 | HEX(string[pos + 1]);
        bytes.data[i] = byte;
    }

    const hash hash = {
        .bytes = bytes,
        .type = HASH_SHA256
    };
    free(string);
    return hash;
}

static size_t size_from_file() {
    FILE *file = fopen(SIZE_FILE_PATH, "r");
    size_t size;
    fscanf(file, "%lu", &size);
    fclose(file);
    return size;
}
