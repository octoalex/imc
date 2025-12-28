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

add_library(imc)

configure_file(public/imc/imc/config.in.h public/imc/imc/config.h)

target_compile_features(imc PRIVATE c_std_23)

target_enable_warnings(imc)

target_sources(
        imc

        PRIVATE
        src/linux/launch_process.c

        PUBLIC
        FILE_SET imc_public_headers
        TYPE HEADERS
        BASE_DIRS public "${CMAKE_CURRENT_BINARY_DIR}/public"

        PRIVATE
        FILE_SET imc_private_headers
        TYPE HEADERS
        BASE_DIRS private
)

target_link_libraries(imc PRIVATE m imc::fetch imc::common)

add_library(imc::imc ALIAS imc)

add_subdirectory(tests)
