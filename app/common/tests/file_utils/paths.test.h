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
 * Created by octoalex on 18/12/2025.
 */

#ifndef IMC_PATHS_TEST_H
#define IMC_PATHS_TEST_H

const char *const PATH_SIMPLE_RELATIVE                = "a/b/c";
const char *const PATH_SIMPLE_RELATIVE_TRAILING       = "a/b/c/";
const char *const PATH_SIMPLE_ABSOLUTE                = "/e/f/g";
const char *const PATH_SIMPLE_ABSOLUTE_TRAILING       = "/e/f/g/";
const char *const PATH_SELF_RELATIVE                  = ".a././.b././.c.";
const char *const PATH_SELF_RELATIVE_TRAILING         = ".a././.b././.c./";
const char *const PATH_SELF_ABSOLUTE                  = "/.e././.f././.g.";
const char *const PATH_SELF_ABSOLUTE_TRAILING         = "/.e././.f././.g./";
const char *const PATH_UP_RELATIVE                    = "..a../..b../../..c..";
const char *const PATH_UP_RELATIVE_TRAILING           = "..a../..b../../..c../";
const char *const PATH_UP_ABSOLUTE                    = "/..e../..f../../..g..";
const char *const PATH_UP_ABSOLUTE_TRAILING           = "/..e../..f../../..g../";
const char *const PATH_NULL_RELATIVE                  = "..a../../..b../../..c../..";
const char *const PATH_NULL_RELATIVE_TRAILING         = "..a../../..b../../..c../../";
const char *const PATH_NULL_ABSOLUTE                  = "/..e../../..f../../..g../..";
const char *const PATH_NULL_ABSOLUTE_TRAILING         = "/..e../../..f../../..g../../";
const char *const PATH_DEFICIT_SLIM_RELATIVE          = "a/b/c/../../../..";
const char *const PATH_DEFICIT_SLIM_RELATIVE_TRAILING = "a/b/c/../../../../";
const char *const PATH_DEFICIT_SLIM_ABSOLUTE          = "/e/f/g/../../../..";
const char *const PATH_DEFICIT_SLIM_ABSOLUTE_TRAILING = "/e/f/g/../../../../";
const char *const PATH_DEFICIT_DEEP_RELATIVE          = "a/b/c/../../../../../..";
const char *const PATH_DEFICIT_DEEP_RELATIVE_TRAILING = "a/b/c/../../../../../../";
const char *const PATH_DEFICIT_DEEP_ABSOLUTE          = "/e/f/g/../../../../../..";
const char *const PATH_DEFICIT_DEEP_ABSOLUTE_TRAILING = "/e/f/g/../../../../../../";
const char *const PATH_MIXED_RELATIVE                 = "a/../b/../.././c";
const char *const PATH_MIXED_RELATIVE_TRAILING        = "a/../b/../.././c/";
const char *const PATH_MIXED_ABSOLUTE                 = "/e/../f/../.././g";
const char *const PATH_MIXED_ABSOLUTE_TRAILING        = "/e/../f/../.././g/";

#define TEST_SINGLE(function, base, type)                                                                              \
    buffer = function(type);                                                                                           \
    if (strcmp(buffer, base) != 0) {                                                                                   \
        fprintf(stderr, "Test " #type " failed! Expected \"%s\", got instead \"%s\"\n", base, buffer);                 \
        any_failed = true;                                                                                             \
    }                                                                                                                  \
    free(buffer);

#define TEST(function, type)                                                                                           \
    TEST_SINGLE(function, PATH_##type##_RELATIVE_OUTPUT, PATH_##type##_RELATIVE)                                       \
    TEST_SINGLE(function, PATH_##type##_RELATIVE_OUTPUT, PATH_##type##_RELATIVE_TRAILING)                              \
    TEST_SINGLE(function, PATH_##type##_ABSOLUTE_OUTPUT, PATH_##type##_ABSOLUTE)                                       \
    TEST_SINGLE(function, PATH_##type##_ABSOLUTE_OUTPUT, PATH_##type##_ABSOLUTE_TRAILING)

#endif //IMC_PATHS_TEST_H
