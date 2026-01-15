#!/bin/bash

# This file is part of octoalex's app (https://github.com/octoalex/imc).
# Copyright (c) 2025 octoalex.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# Script to run tests

# Variables
source common.sh

# Run tests
echo
echo -e "${blue}GCC Ninja Start${nc}"
ctest --test-dir $gcc_ninja
export gcc_ninja_exit=$?
echo -e "${blue}GCC Ninja Done${nc}"
echo
echo -e "${blue}GCC Make Start${nc}"
ctest --test-dir $gcc_make
export gcc_make_exit=$?
echo -e "${blue}GCC Make Done${nc}"
echo
echo -e "${blue}Clang Ninja Start${nc}"
ctest --test-dir $clang_ninja
export clang_ninja_exit=$?
echo -e "${blue}Clang Ninja Done${nc}"
echo
echo -e "${blue}Clang Make Start${nc}"
ctest --test-dir $gcc_make
export clang_make_exit=$?
echo -e "${blue}Clang Make Done${nc}"
echo

echo_results "test"
