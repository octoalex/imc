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

    bool any = false;
    for (size_t i = 0; i < count; ++i) {
        if (is_hash_valid(&test_hashes[i]) != VALIDITY[i]) {
            any = true;
            fprintf(stderr, "Hash %ld is %s, but is_hash_valid found it to be %s!\n",
                i, index_to_name(i), !VALIDITY[i] ? "valid" : "invalid"
            );
        }
    }
    return any ? -1 : 0;
}
