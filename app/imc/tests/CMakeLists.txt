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

# This tests basic launch_process and wait_process functionality
add_test_executable(imc::imc base_process launch_process/base_process.test.c)
add_test(NAME base_process COMMAND base_process)

# This tests is_process_alive functionality
add_test_executable(imc::imc is_process_alive launch_process/is_process_alive.test.c)
add_test(NAME is_process_alive COMMAND is_process_alive)

# This tests if file descriptors are inherited by launched processes
add_test_executable(
        imc::imc process_file_descriptor_inheritance launch_process/process_file_descriptor_inheritance.test.c
)
add_test(NAME process_file_descriptor_inheritance COMMAND process_file_descriptor_inheritance)

# This tests setting custom STDIN, STDOUT and STDERR
add_test_executable(imc::imc pipe_process_communication launch_process/pipe_process_communication.test.c)
target_link_libraries(pipe_process_communication PRIVATE imc::common)
add_test(NAME pipe_process_communication COMMAND pipe_process_communication)
set_tests_properties(pipe_process_communication PROPERTIES TIMEOUT 3)

# This tests changing the working directory
add_test_executable(imc::imc change_process_working_dir launch_process/change_process_working_dir.test.c)
add_test(NAME change_process_working_dir COMMAND change_process_working_dir ${CMAKE_SOURCE_DIR})

# This tests killing a process
add_test_executable(imc::imc kill_process launch_process/kill_process.test.c)
add_test(NAME kill_process COMMAND kill_process)
