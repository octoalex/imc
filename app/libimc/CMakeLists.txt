# This file is part of octoalex's imc (https://github.com/octoalex/imc).
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

# This directory contains the launcher logic

add_library(libimc)

configure_file(public/imc/libimc/config.in.h public/imc/libimc/config.h)

target_compile_features(libimc PRIVATE c_std_23)

target_sources(
        libimc

        PRIVATE
        src/linux/launch_process.c

        PUBLIC
        FILE_SET libimc_public_headers
        TYPE HEADERS
        BASE_DIRS public "${CMAKE_CURRENT_BINARY_DIR}/public"

        PRIVATE
        FILE_SET libimc_private_headers
        TYPE HEADERS
        BASE_DIRS private
)

target_link_libraries(libimc PRIVATE m imc::libfetch)

add_library(imc::libimc ALIAS libimc)

add_subdirectory(tests)
