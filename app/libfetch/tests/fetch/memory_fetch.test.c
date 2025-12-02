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
 * Created by octoalex on 02/12/2025.
 */

#include <imc/fetch/fetch.h>

const char *const TEST_URL = "https://www.example.com/";
const char *const CURL_FILE_PATH = "curl.html";
constexpr size_t COMPARE_SIZE = 32;

void print_byte_comparison(const char *a, const char *b, size_t a_size, size_t b_size, size_t point);
void print_byte_array(const char *array, size_t size, size_t point);
void print_special_char(char c);

int main(const int argc, const char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Expected no arguments, but got %d!\n", argc - 1);
        return -1;
    }

    if (!setup_fetch()) {
        fprintf(stderr, "Fetch setup has failed!\n");
        return -1;
    }

    // fetch to memory
    uint8_t *data;
    size_t size;

    if (!fetch(TEST_URL, &data, &size)) {
        // fetch has failed, abort
        fprintf(stderr, "Fetch has failed!\n");
        return -1;
    }

    // get reference file
    FILE *curl = fopen(CURL_FILE_PATH, "r");

    char *reference = nullptr;
    size_t reference_size = 0;
    getdelim(&reference, &reference_size, EOF, curl);
    // reference size is the calloc size, not the actual filesize, so it will be reduced by 1
    --reference_size;

    // first, check if the sizes are the same
    size_t point = -1;
    const size_t min_size = size < reference_size ? size : reference_size;
    if (size != reference_size) {
        fprintf(stderr, "Size mismatch! fetch downloads %ld bytes, reference is %ld long!\n", size, reference_size);
        point = min_size;
    }
    for (size_t i = 0; i < min_size; ++i) {
        if (data[i] != reference[i]) {
            fprintf(stderr, "Data mismatch at position %ld! fetch downloaded %d ('", i, data[i]);
            print_special_char((char)data[i]);
            fprintf(stderr, "') while reference is %d ('", reference[i]);
            print_special_char(reference[i]);
            fprintf(stderr, "')\n");
            // set the point, and exit the loop
            point = i;
            break;
        }
    }
    if (point != -1) {
        print_byte_comparison((const char *)data, reference, size, reference_size, point);
        return -1;
    }
    return 0;
}

void print_byte_comparison(const char *a, const char *b, const size_t a_size, const size_t b_size, const size_t point) {
    fprintf(stderr, "\t\t ");
    for (size_t i = 0; i < COMPARE_SIZE; ++i) {
        fprintf(stderr, " %02lx", i);
    }
    fprintf(stderr, "\nfetch\t\t:");
    print_byte_array(a, a_size, point);
    fprintf(stderr, "\nreference\t:");
    print_byte_array(b, b_size, point);
    fprintf(stderr, "\n");
}

void print_byte_array(const char *array, const size_t size, const size_t point) {
    const size_t base = point - COMPARE_SIZE / 2 > 0 ? point - COMPARE_SIZE / 2 : 0;
    const size_t limit = base + COMPARE_SIZE < size ? base + COMPARE_SIZE : size;
    for (size_t i = base; i < limit; ++i) {
        fprintf(stderr, " %02x", array[i]);
    }
    for (size_t i = size; i < base + COMPARE_SIZE; ++i) {
        fprintf(stderr, " --");
    }
}


void print_special_char(const char c) {
    switch (c) {
    case '\a':
        fprintf(stderr, "\\a");
        break;
    case '\b':
        fprintf(stderr, "\\b");
        break;
    case '\f':
        fprintf(stderr, "\\f");
        break;
    case '\n':
        fprintf(stderr, "\\n");
        break;
    case '\r':
        fprintf(stderr, "\\r");
        break;
    case '\t':
        fprintf(stderr, "\\t");
        break;
    case '\v':
        fprintf(stderr, "\\v");
        break;
    case '\\':
        fprintf(stderr, "\\\\");
        break;
    case '\'':
        fprintf(stderr, "\\'");
        break;
    case '\"':
        fprintf(stderr, "\\\"");
        break;
    default:
        fprintf(stderr, "%c", c);
    }
}
