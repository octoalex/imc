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

add_test_executable(imc::libimc base_launch_process base_launch_process.test.c)
add_test_executable(imc::libimc alive_launch_process alive_launch_process.test.c)
add_test_executable(imc::libimc file_descriptor_launch_process file_descriptor_launch_process.test.c)
add_test_executable(imc::libimc pipe_launch_process pipe_launch_process.test.c)

add_test(NAME base_launch_process COMMAND base_launch_process)
add_test(NAME alive_launch_process COMMAND alive_launch_process)
add_test(NAME file_descriptor_launch_process COMMAND file_descriptor_launch_process)
add_test(NAME pipe_launch_process COMMAND pipe_launch_process)
set_tests_properties(pipe_launch_process PROPERTIES TIMEOUT 3)