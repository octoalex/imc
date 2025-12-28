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

const char *const TEXT_A = "Hello, I am a string, and I like goth men, women and non-binary people";
const char *const TEXT_B = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse tincidunt nibh aliquet"
    " faucibus laoreet. Cras fermentum urna et sodales rhoncus. Sed consequat lacus id nulla condimentum, vitae commodo"
    " dolor lacinia. Nam sodales. ";
const char *const TEXT_C = "A quotation circulates on the Internet, attributed to me, but it wasn't written by me. \n"
    "Here's the text that is circulating. Most of it was copied from statements I have made, but the part italicized"
    " here is not from me. It makes points that are mistaken or confused.\n"
    "I'd just like to interject for a moment. What you're referring to as Linux, is in fact, GNU/Linux, or as I've"
    " recently taken to calling it, GNU plus Linux. Linux is not an operating system unto itself, but rather another"
    " free component of a fully functioning GNU system made useful by the GNU corelibs, shell utilities and vital"
    " system components comprising a full OS as defined by POSIX. Many computer users run a modified version of the GNU"
    " system every day, without realizing it. Through a peculiar turn of events, the version of GNU which is widely"
    " used today is often called “Linux,” and many of its users are not aware that it is basically the GNU system,"
    " developed by the GNU Project. There really is a Linux, and these people are using it, but it is just a part of"
    " the system they use.\n"
    "Linux is the kernel: the program in the system that allocates the machine's resources to the other programs that"
    " you run. The kernel is an essential part of an operating system, but useless by itself; it can only function in"
    " the context of a complete operating system. Linux is normally used in combination with the GNU operating system:"
    " the whole system is basically GNU with Linux added, or GNU/Linux. All the so-called “Linux” distributions are"
    " really distributions of GNU/Linux.\n"
    "The main error is that Linux is not strictly speaking part of the GNU system—whose kernel is GNU Hurd. The version"
    " with Linux, we call “GNU/Linux.” It is OK to call it “GNU” when you want to be really short, but it is better to"
    " call it “GNU/Linux” so as to give Torvalds some credit.\n"
    "We don't use the term “corelibs,” and I am not sure what that would mean, but GNU is much more than the specific"
    " packages we developed for it. I set out in 1983 to develop an operating system, calling it GNU, and that job"
    " required developing whichever important packages we could not find elsewhere.\n";

const uint8_t SHA1_A_BYTES[] = {
    0x27, 0xc4, 0x5f, 0x64,
    0xa7, 0x71, 0x0c, 0x16,
    0x0b, 0x4d, 0x5c, 0x70,
    0xe1, 0x67, 0x8e, 0x4b,
    0xea, 0xef, 0xb0, 0xff
};
const uint8_t SHA1_B_BYTES[] = {
    0xf1, 0x01, 0xa0, 0xbb,
    0xd0, 0x63, 0x47, 0x07,
    0x62, 0xc8, 0x99, 0xe4,
    0x73, 0x05, 0xc8, 0xc0,
    0xc6, 0x2f, 0x02, 0x78
};
const uint8_t SHA1_C_BYTES[] = {
    0x47, 0x64, 0xe9, 0x4b,
    0xdf, 0x97, 0xd6, 0xa8,
    0x3e, 0x88, 0x56, 0x26,
    0x4b, 0xbf, 0x1e, 0x66,
    0x21, 0x1a, 0x6a, 0x0a
};

const uint8_t SHA256_A_BYTES[] = {
    0x67, 0x7a, 0xdf, 0x30,
    0x50, 0x71, 0x4f, 0x89,
    0x44, 0x47, 0xa9, 0x43,
    0xbc, 0x28, 0xc5, 0xf9,
    0xb8, 0x28, 0x66, 0x58,
    0x72, 0xc8, 0x55, 0x8e,
    0x21, 0x26, 0x7a, 0x9a,
    0x7b, 0x05, 0xdd, 0xe5
};
const uint8_t SHA256_B_BYTES[] = {
    0x59, 0xb1, 0xbe, 0x02,
    0xcb, 0xa3, 0xc9, 0xb0,
    0xc3, 0xe1, 0xf9, 0x7e,
    0xf5, 0x5a, 0x07, 0x31,
    0x3a, 0xe8, 0x0f, 0x18,
    0x77, 0xb7, 0xb4, 0x98,
    0xb3, 0x41, 0x54, 0xd1,
    0x5f, 0xfb, 0x49, 0x44
};
const uint8_t SHA256_C_BYTES[] = {
    0x4f, 0x73, 0x03, 0xe4,
    0xbd, 0xab, 0x0e, 0x61,
    0x30, 0x08, 0x5f, 0xba,
    0x8e, 0x87, 0xb8, 0xb4,
    0x07, 0x37, 0x73, 0xc6,
    0x9b, 0x6b, 0x2b, 0xca,
    0xeb, 0xd9, 0x73, 0x0a,
    0xe1, 0x32, 0xfb, 0x94
};

const uint8_t SHA512_A_BYTES[] = {
    0x7a, 0x3c, 0xf8, 0x3c,
    0xe8, 0xfc, 0x69, 0x0e,
    0x74, 0x38, 0xff, 0x91,
    0xfc, 0xbd, 0x9f, 0x73,
    0x09, 0x51, 0x8a, 0xbd,
    0xc4, 0x0d, 0xa9, 0x85,
    0xc6, 0x08, 0x70, 0x66,
    0x8f, 0x4e, 0x71, 0xfc,
    0x06, 0x35, 0xae, 0xd7,
    0xe9, 0xe9, 0x6b, 0xbe,
    0xfb, 0xca, 0x91, 0xd1,
    0x64, 0x97, 0xba, 0x40,
    0x34, 0x1f, 0x82, 0x20,
    0x98, 0xba, 0x72, 0xa7,
    0x0e, 0xc9, 0x46, 0x66,
    0x61, 0x52, 0xca, 0x09
};
const uint8_t SHA512_B_BYTES[] = {
    0x89, 0x39, 0x92, 0x9a,
    0x2b, 0x81, 0x46, 0x45,
    0x3f, 0xbc, 0xa1, 0xb7,
    0x7b, 0x47, 0xec, 0x24,
    0x6b, 0x47, 0xc4, 0x1a,
    0x08, 0xaa, 0x27, 0x87,
    0x0a, 0x0c, 0xd1, 0x8f,
    0xa9, 0x86, 0xf8, 0x2a,
    0xc0, 0x7b, 0xb8, 0x9f,
    0x9d, 0xad, 0xa2, 0x32,
    0x06, 0x13, 0x43, 0xd9,
    0x4e, 0x12, 0x53, 0x49,
    0xea, 0xd0, 0x13, 0x4a,
    0x72, 0x7b, 0xd9, 0x91,
    0x5c, 0x78, 0xae, 0x81,
    0xcd, 0xd5, 0xe5, 0xe7
};
const uint8_t SHA512_C_BYTES[] = {
    0x8b, 0x4e, 0x3f, 0xe1,
    0xed, 0x61, 0x96, 0x7c,
    0xd8, 0xf8, 0x45, 0x43,
    0x5b, 0x66, 0x0d, 0x4a,
    0xd9, 0xec, 0xc8, 0x1e,
    0x24, 0xea, 0x8b, 0xbd,
    0x23, 0x61, 0xef, 0x73,
    0x75, 0x2b, 0x7a, 0xe4,
    0xb1, 0xd4, 0x4d, 0x77,
    0x3b, 0x7c, 0xa4, 0xf0,
    0xc8, 0x28, 0x90, 0x77,
    0x63, 0x86, 0x14, 0xd4,
    0x90, 0x59, 0x19, 0x51,
    0x15, 0x36, 0x32, 0x76,
    0x9b, 0x80, 0xa7, 0x13,
    0x5b, 0x70, 0xd2, 0xb3
};

#define TEST_HASH(cat, typ)                                                                                            \
    const hash sha##typ##_##cat = {                                                                                    \
        .type = HASH_SHA##typ,                                                                                         \
        .bytes = from_data(SHA##typ##_##cat##_BYTES, sizeof(SHA##typ##_##cat##_BYTES))                                 \
    };                                                                                                                 \
    if (!validate_bytes(&text_##cat##_bytes, &sha##typ##_##cat)) {                                                     \
        fprintf(stderr, "SHA" #typ " has failed for Text " #cat "\n");                                                 \
        any = true;                                                                                                    \
    }

int main() {
    const byte_array text_A_bytes = from_c_string(TEXT_A);
    const byte_array text_B_bytes = from_c_string(TEXT_B);
    const byte_array text_C_bytes = from_c_string(TEXT_C);

    bool any = false;

    TEST_HASH(A, 1);
    TEST_HASH(B, 1);
    TEST_HASH(C, 1);
    TEST_HASH(A, 256);
    TEST_HASH(B, 256);
    TEST_HASH(C, 256);
    TEST_HASH(A, 512);
    TEST_HASH(B, 512);
    TEST_HASH(C, 512);

    return any ? -1 : 0;
}
