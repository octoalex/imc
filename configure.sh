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

# Simple script to set up cmake with different configurations for compatibility

# Variables
source common.sh

# Set base values for the executables
if [ -z "${GCC+x}" ]
then
  export GCC="gcc"
fi
if [ -z "${CLANG+x}" ]
then
  export CLANG="clang"
fi

# Configure
echo
echo -e "${blue}GCC Ninja Start${nc}"
cmake .               \
  -B $gcc_ninja       \
  -G Ninja            \
  -D "CMAKE_C_COMPILER=$GCC"
echo -e "${blue}GCC Ninja Done${nc}"
echo
echo -e "${blue}GCC Make Start${nc}"
cmake .               \
  -B $gcc_make        \
  -G "Unix Makefiles" \
  -D "CMAKE_C_COMPILER=$GCC"
echo -e "${blue}GCC Make Done${nc}"
echo
echo -e "${blue}Clang Ninja Start${nc}"
cmake .               \
  -B $clang_ninja     \
  -G Ninja            \
  -D "CMAKE_C_COMPILER=$CLANG"
echo -e "${blue}Clang Ninja Done${nc}"
echo
echo -e "${blue}Clang Make Start${nc}"
cmake .               \
  -B $clang_make      \
  -G "Unix Makefiles" \
  -D "CMAKE_C_COMPILER=$CLANG"
echo -e "${blue}Clang Make Done${nc}"
echo
