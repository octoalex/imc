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

# Commonly used variables

# Paths
export gcc_ninja="cmake-build-gcc-ninja"
export gcc_make="cmake-build-gcc-make"
export clang_ninja="cmake-build-clang-ninja"
export clang_make="cmake-build-clang-make"

# Colors
export nc="\033[0m"
export red="\033[0;31m"
export blue="\033[0;34m"
export green="\033[0;32m"

# Print Results
function echo_results {
  if [ $gcc_ninja_exit -eq 0 ]
  then
    echo -e "${green}GCC Ninja $1 successful${nc}"
  else
    echo -e "${red}GCC Ninja $1 failed!${nc}"
  fi
  if [ $gcc_make_exit -eq 0 ]
  then
    echo -e "${green}GCC Make $1 successful${nc}"
  else
    echo -e "${red}GCC Make $1 failed!${nc}"
  fi
  if [ $clang_ninja_exit -eq 0 ]
  then
    echo -e "${green}Clang Ninja $1 successful${nc}"
  else
    echo -e "${red}Clang Ninja $1 failed!${nc}"
  fi
  if [ $clang_make_exit -eq 0 ]
  then
    echo -e "${green}Clang Make $1 successful${nc}"
  else
    echo -e "${red}Clang Make $1 failed!${nc}"
  fi
}
