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
add_test_executable(imc::libimc base_launch_process base_launch_process.test.c)
add_test(NAME base_launch_process COMMAND base_launch_process)

# This tests is_process_alive functionality
add_test_executable(imc::libimc alive_launch_process alive_launch_process.test.c)
add_test(NAME alive_launch_process COMMAND alive_launch_process)

# This tests if file descriptors are inherited by launched processes
add_test_executable(imc::libimc file_descriptor_launch_process file_descriptor_launch_process.test.c)
add_test(NAME file_descriptor_launch_process COMMAND file_descriptor_launch_process)

# This tests setting custom STDIN, STDOUT and STDERR
add_test_executable(imc::libimc pipe_launch_process pipe_launch_process.test.c)
add_test(NAME pipe_launch_process COMMAND pipe_launch_process)
set_tests_properties(pipe_launch_process PROPERTIES TIMEOUT 3)

# This tests changing the working directory
add_test_executable(imc::libimc working_dir_launch_process working_dir_launch_process.test.c)
add_test(NAME working_dir_launch_process COMMAND working_dir_launch_process ${CMAKE_SOURCE_DIR})

# This tests killing a process
add_test_executable(imc::libimc kill_launch_process kill_launch_process.test.c)
add_test(NAME kill_launch_process COMMAND kill_launch_process)
