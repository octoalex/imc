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

#include <string.h>
#include <imc/fetch/hash.h>
#include <openssl/sha.h>

constexpr size_t SHA1_SIZE = 160 / 8;
constexpr size_t SHA256_SIZE = 256 / 8;
constexpr size_t SHA512_SIZE = 512 / 8;

static size_t get_hash_size(hash_type type);

hash get_hash(const byte_array *data, const hash_type type) {
    if (type == HASH_NULL) return NULL_HASH;
    const size_t size = get_hash_size(type);
    const byte_array hash_bytes = alloc_byte_array(size);
    switch (type) {
    case HASH_SHA1:
        SHA1(data->data, data->size, hash_bytes.data);
        break;
    case HASH_SHA256:
        SHA256(data->data, data->size, hash_bytes.data);
        break;
    case HASH_SHA512:
        SHA512(data->data, data->size, hash_bytes.data);
        break;
    default:
    }
    const hash hash = {
        .type = type,
        .bytes = hash_bytes
    };
    return hash;
}

bool is_hash_valid(const hash *hash) {
    if (hash->type == HASH_NULL || hash->bytes.data == nullptr || hash->bytes.size == 0) {
        return false;
    }
    return hash->bytes.size == get_hash_size(hash->type);
}

bool is_hash_null(const hash *hash) {
    return hash->type == HASH_NULL && hash->bytes.data == nullptr && hash->bytes.size == 0;
}

bool compare_hash(const hash *lhs, const hash *rhs) {
    // both hashes must be valid
    if (!is_hash_valid(lhs) || !is_hash_valid(rhs)) {
        return false;
    }

    // both hashes must be of the same type
    if (lhs->type != rhs->type) {
        return false;
    }

    return memcmp(lhs->bytes.data, rhs->bytes.data, lhs->bytes.size) == 0;
}

bool validate_bytes(const byte_array *data, const hash *data_hash) {
    // validate initial hash
    if (!is_hash_valid(data_hash)) {
        return false;
    }

    const hash new = get_hash(data, data_hash->type);
    const bool equal = compare_hash(data_hash, &new);
    free_hash_unsafe(&new);
    return equal;
}

void free_hash(hash *hash) {
    free_byte_array_unsafe(hash->bytes);
    *hash = NULL_HASH;
}

void free_hash_unsafe(const hash *hash) {
    free_byte_array_unsafe(hash->bytes);
}

// helpers

static size_t get_hash_size(const hash_type type) {
    switch (type) {
        case HASH_SHA1:   return SHA1_SIZE;
        case HASH_SHA256: return SHA256_SIZE;
        case HASH_SHA512: return SHA512_SIZE;
        default: return 0;
    }
}
