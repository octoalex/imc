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

#include <stdlib.h>
#include <string.h>
#include <imc/common/file_utils.h>
#include <stdio.h>

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

const char *const PATH_SIMPLE_RELATIVE_OUTPUT         = "a/b/c";
const char *const PATH_SIMPLE_ABSOLUTE_OUTPUT         = "/e/f/g";
const char *const PATH_SELF_RELATIVE_OUTPUT           = ".a./.b./.c.";
const char *const PATH_SELF_ABSOLUTE_OUTPUT           = "/.e./.f./.g.";
const char *const PATH_UP_RELATIVE_OUTPUT             = "..a../..c..";
const char *const PATH_UP_ABSOLUTE_OUTPUT             = "/..e../..g..";
const char *const PATH_NULL_RELATIVE_OUTPUT           = ".";
const char *const PATH_NULL_ABSOLUTE_OUTPUT           = "/";
const char *const PATH_DEFICIT_SLIM_RELATIVE_OUTPUT   = "..";
const char *const PATH_DEFICIT_SLIM_ABSOLUTE_OUTPUT   = "/..";
const char *const PATH_DEFICIT_DEEP_RELATIVE_OUTPUT   = "../../..";
const char *const PATH_DEFICIT_DEEP_ABSOLUTE_OUTPUT   = "/../../..";
const char *const PATH_MIXED_RELATIVE_OUTPUT          = "../c";
const char *const PATH_MIXED_ABSOLUTE_OUTPUT          = "/../g";

#define TEST_SINGLE(base, type)                                                                                        \
    buffer = clean_path(type);                                                                                         \
    if (strcmp(buffer, base) != 0) {                                                                                   \
        fprintf(stderr, "Test PATH_" #type " failed! Expected \"%s\", got instead \"%s\"\n", base, buffer);            \
        any_failed = true;                                                                                             \
    }                                                                                                                  \
    free((void *)buffer);

#define TEST(type)                                                                                                     \
    TEST_SINGLE(PATH_##type##_RELATIVE_OUTPUT, PATH_##type##_RELATIVE)                                                 \
    TEST_SINGLE(PATH_##type##_RELATIVE_OUTPUT, PATH_##type##_RELATIVE_TRAILING)                                        \
    TEST_SINGLE(PATH_##type##_ABSOLUTE_OUTPUT, PATH_##type##_ABSOLUTE)                                                 \
    TEST_SINGLE(PATH_##type##_ABSOLUTE_OUTPUT, PATH_##type##_ABSOLUTE_TRAILING)

int main() {
    bool any_failed = false;
    const char *buffer;

    TEST(SIMPLE);
    TEST(SELF);
    TEST(UP);
    TEST(NULL);
    TEST(DEFICIT_SLIM);
    TEST(DEFICIT_DEEP);
    TEST(MIXED);

    return any_failed ? -1 : 0;
}
