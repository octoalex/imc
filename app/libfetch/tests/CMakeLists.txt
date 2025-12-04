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

# setup
add_test(NAME curl_setup COMMAND curl https://www.example.com/ -o curl.html)

# Check if fetch performs like the curl command
add_test_executable(imc::libfetch memory_fetch fetch/memory_fetch.test.c)
add_test(NAME memory_fetch COMMAND memory_fetch)

# Check if fetch_to_file performs like the curl command
add_test_executable(imc::libfetch file_fetch fetch/file_fetch.test.c)
add_test(NAME file_fetch COMMAND file_fetch)

# cleanup
add_test(NAME curl_cleanup COMMAND rm curl.html)

# set fixtures
set_tests_properties(memory_fetch file_fetch PROPERTIES FIXTURES_REQUIRED fetch)
set_tests_properties(curl_setup PROPERTIES FIXTURES_SETUP fetch)
set_tests_properties(curl_cleanup PROPERTIES FIXTURES_CLEANUP fetch)
