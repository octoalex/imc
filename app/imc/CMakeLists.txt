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

# This directory contains the cli frontend of the app

add_executable(imc)

target_compile_features(imc PRIVATE c_std_23)

target_sources(
    imc

    # both src files and headers are private
    PRIVATE
    src/main.c

    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS private
)
