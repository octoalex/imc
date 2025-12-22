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

FetchContent_Declare(json-c
        GIT_REPOSITORY https://github.com/json-c/json-c.git
        GIT_REMOTE_NAME origin
        GIT_TAG origin/master
)
FetchContent_MakeAvailable(json-c)
add_library(json-c::json-c ALIAS json-c)
