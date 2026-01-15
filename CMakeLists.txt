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

cmake_minimum_required(VERSION 3.23)

project(imc VERSION 0.0.0)

# Includes
include(cmake/test_functions.cmake)
include(cmake/target_functions.cmake)
include(FetchContent)

# Options and variables
set(${CMAKE_PROJECT_NAME}_VERSION_NAME "Skeleton")

option(BUILD_TESTING "Enable tests" ON)
option(CMAKE_COMPILE_WARNING_AS_ERROR "Warnings get turned into errors" ON)

if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU" AND ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  option(DISABLE_BUILD_ID "Unique id for each build" OFF)
elseif (NOT ${DISABLE_BUILD_ID})
  message("Build ids are not supported for compiler \"${CMAKE_C_COMPILER_ID}\", disabling them")
  set(DISABLE_BUILD_ID ON)
endif ()

string(TIMESTAMP ${CMAKE_PROJECT_NAME}_CONFIGURE_TIMESTAMP)
set(${CMAKE_PROJECT_NAME}_GENERATED_DISCLAIMER "/*
 * File generated at ${${CMAKE_PROJECT_NAME}_CONFIGURE_TIMESTAMP}
 * Please do not edit
 */"
)

set(SYSTEM_ID ${CMAKE_SYSTEM_NAME})
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(SYSTEM_TYPE Linux)
endif ()

if(${BUILD_TESTING})
  enable_testing()
endif()

# Add targets
add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(docs)
