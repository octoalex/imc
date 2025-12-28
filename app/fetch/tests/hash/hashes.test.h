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
 * Created by octoalex on 22/12/2025.
 */

#ifndef IMC_HASHES_TEST_H
#define IMC_HASHES_TEST_H

const char *const SHA1_SIZED_STRING = "aaaaaaaaaaaaaaaaaaaa";
const char *const SHA256_SIZED_STRING = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
const char *const SHA512_SIZED_STRING = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

#define TEST_HASHES() {                                                                                                \
    { .type = HASH_SHA1, .bytes = from_c_string(SHA1_SIZED_STRING) },                                                  \
    { .type = HASH_SHA1, .bytes = EMPTY_BYTE_ARRAY },                                                                  \
    { .type = HASH_SHA256, .bytes = from_c_string(SHA256_SIZED_STRING) },                                              \
    { .type = HASH_SHA256, .bytes = EMPTY_BYTE_ARRAY },                                                                \
    { .type = HASH_SHA512, .bytes = from_c_string(SHA512_SIZED_STRING) },                                              \
    { .type = HASH_SHA512, .bytes = EMPTY_BYTE_ARRAY },                                                                \
    { .type = HASH_NULL, .bytes = EMPTY_BYTE_ARRAY }                                                                   \
}

constexpr bool VALIDITY[] = { true, false, true, false, true, false, false };

static const char *index_to_name(const size_t index) {
    switch (index) {
    case 0: return "sha1 valid";
    case 1: return "sha1 invalid";
    case 2: return "sha256 valid";
    case 3: return "sha256 invalid";
    case 4: return "sha512 valid";
    case 5: return "sha512 invalid";
    case 6: return "null";
    default: return "unknown";
    }
}

#endif //IMC_HASHES_TEST_H
