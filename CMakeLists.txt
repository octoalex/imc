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

if(${BUILD_TESTING})
    enable_testing()

    function(create_basic_test test_target name sources command_args)
        add_executable(${name})

        target_compile_features(${name} PRIVATE c_std_23)

        target_sources(
            ${name}

            PRIVATE ${sources}

            PRIVATE
                FILE_SET HEADERS
                BASE_DIRS $<TARGET_PROPERTY:${test_target},INCLUDE_DIRECTORIES>
        )

        target_link_libraries(${name} PRIVATE ${test_target})

        add_test(
            NAME ${name}
            COMMAND ${name} ${command_args}
        )
    endfunction()
endif()

add_subdirectory(app)
