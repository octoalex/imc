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

# Check if web_request_memory performs like the curl command
add_test_executable(imc::libfetch web_request_memory web_request/web_request_memory.test.c)
add_test(NAME web_request_memory COMMAND web_request_memory)

# Check if web_request_file performs like the curl command
add_test_executable(imc::libfetch web_request_file web_request/web_request_file.test.c)
add_test(NAME web_request_file COMMAND web_request_file)

# cleanup
add_test(NAME curl_cleanup COMMAND rm curl.html)

# set fixtures
set_tests_properties(web_request_memory web_request_file PROPERTIES FIXTURES_REQUIRED web_request)
set_tests_properties(curl_setup PROPERTIES FIXTURES_SETUP web_request)
set_tests_properties(curl_cleanup PROPERTIES FIXTURES_CLEANUP web_request)
