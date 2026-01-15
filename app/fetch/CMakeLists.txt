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

# Find Packages
find_package(OpenSSL REQUIRED)

add_library(fetch)

target_compile_features(fetch PRIVATE c_std_23)
target_sources(fetch
  PRIVATE
    src/web_request.c
    src/hash.c
    src/fetch.c
    src/fetch_format.c

  PUBLIC
    FILE_SET fetch_public_headers
    TYPE HEADERS
    BASE_DIRS
      public

  PRIVATE
    FILE_SET fetch_private_headers
    TYPE HEADERS
    BASE_DIRS
      private
)

target_link_libraries(fetch PRIVATE curl OpenSSL::Crypto PUBLIC imc::common json-c::json-c)

add_library(imc::fetch ALIAS fetch)

add_subdirectory(tests)