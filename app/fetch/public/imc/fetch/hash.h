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

#ifndef IMC_HASH_H
#define IMC_HASH_H

#include <imc/common/byte_array.h>

/// The hash type
typedef enum hash_type {
    HASH_NULL,
    HASH_SHA1,
    HASH_SHA256,
    HASH_SHA512
} hash_type;

/// A hash
typedef struct hash {
    /// The type of the hash
    hash_type type;
    /// The actual hash
    byte_array bytes;
} hash;

/// An empty hash, used for empty values
constexpr hash NULL_HASH = { .type = HASH_NULL, .bytes = EMPTY_BYTE_ARRAY };

/// Calculate the hash of a byte array
/// @param data The data to hash
/// @param type The type of hash to calculate
/// @return The hash
hash get_hash(const byte_array *data, hash_type type);

/// Checks if the hash is formatted correctly
/// @param hash The hash to validate
/// @return If the hash is valid
bool is_hash_valid(const hash *hash);

/// Checks if the hash is null
/// @param hash The hash to check
/// @return If the hash is null
bool is_hash_null(const hash *hash);

/// Compare if two hashes match
/// @param lhs The first hash
/// @param rhs The second hash
/// @return Whether the hashes match
/// @note Returns false if any of the hashes is invalid
bool compare_hash(const hash *lhs, const hash *rhs);

/// Checks if the given byte array's hash matches the given hash
/// @param data The data to validate
/// @param data_hash The reference hash
/// @return Whether the data is valid
/// @note Returns false if the hash is invalid
bool validate_bytes(const byte_array *data, const hash *data_hash);

/// Frees a hash
/// @param hash The hash to free
void free_hash(hash *hash);

/// Frees a hash, without setting it to a safe empty value
/// @param hash The hash to free
/// @detail Works exactly like @link free_hash@endlink, but unlike it, it leaves the hash in a potentially unsafe state
void free_hash_unsafe(const hash *hash);

#endif //IMC_HASH_H
