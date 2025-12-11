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

add_library(libcommon)

target_compile_features(libcommon PRIVATE c_std_23)

target_sources(
        libcommon

        PRIVATE
        src/byte_array.c
        src/linux/file_utils.c

        PUBLIC
        FILE_SET libcommon_public_headers
        TYPE HEADERS
        BASE_DIRS public
)

add_library(imc::libcommon ALIAS libcommon)

add_subdirectory(tests)
