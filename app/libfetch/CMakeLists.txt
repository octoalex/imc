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

add_library(libfetch)

target_compile_features(libfetch PRIVATE c_std_23)

target_sources(
        libfetch

        PRIVATE
        src/web_request.c
        src/fetch.c

        PUBLIC
        FILE_SET libfetch_public_headers
        TYPE HEADERS
        BASE_DIRS public

        PRIVATE
        FILE_SET libfetch_private_headers
        TYPE HEADERS
        BASE_DIRS private
)

# libfyaml is included in source through git submodules, so there's no need to find the package
#find_package(libfyaml REQUIRED)

target_link_libraries(libfetch PRIVATE curl libfyaml::libfyaml PUBLIC imc::libcommon)

add_library(imc::libfetch ALIAS libfetch)

add_subdirectory(tests)