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

function(add_test_executable test_target name sources)
    add_executable(${name})

    target_compile_features(${name} PRIVATE c_std_23)

    target_enable_warnings(${name})

    target_sources(
            ${name}

            PRIVATE ${sources}

            PRIVATE
            FILE_SET HEADERS
            BASE_DIRS $<TARGET_PROPERTY:${test_target},INCLUDE_DIRECTORIES>
    )

    target_link_libraries(${name} PRIVATE ${test_target})
endfunction()
