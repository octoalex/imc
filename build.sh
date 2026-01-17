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

# Small script to create and run tests across as many platforms as possible

# Variables
source common.sh

# Set base values for the executables
if [[ -z ${jobs+x} ]]
then
  export jobs=8
fi

echo
echo -e "${blue}GCC Ninja Start${nc}"
cmake --build $gcc_ninja -j "$jobs"
export gcc_ninja_exit=$?
echo -e "${blue}GCC Ninja Done${nc}"
echo
echo -e "${blue}GCC Make Start${nc}"
cmake --build $gcc_make -j "$jobs"
export gcc_make_exit=$?
echo -e "${blue}GCC Make Done${nc}"
echo
echo -e "${blue}Clang Ninja Start${nc}"
cmake --build $clang_ninja -j "$jobs"
export clang_ninja_exit=$?
echo -e "${blue}Clang Ninja Done${nc}"
echo
echo -e "${blue}Clang Make Start${nc}"
cmake --build $gcc_make -j "$jobs"
export clang_make_exit=$?
echo -e "${blue}Clang Make Done${nc}"
echo

echo_results "build"

exit_with_code
