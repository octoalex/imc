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

#include <stdio.h>
#include <imc/fetch/hash.h>
#include "hashes.test.h"

int main() {
    const hash test_hashes[] = TEST_HASHES();
    constexpr size_t count = sizeof(test_hashes) / sizeof(hash);

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < count; ++j) {
            const bool expected = i == j && VALIDITY[i] && VALIDITY[j];
            const bool got = compare_hash(&test_hashes[i], &test_hashes[j]);
            if (got != expected) {
                fprintf(stderr, "Comparing hashes '%s' and '%s' should return %s, but returned %s!\n",
                    index_to_name(i), index_to_name(j), expected ? "true" : "false", got ? "true" : "false");
            }
        }
    }
}
