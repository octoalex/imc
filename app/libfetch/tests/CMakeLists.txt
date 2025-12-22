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

# Check if web_request performs like the curl command
add_test_executable(imc::libfetch web_request web_request/web_request.test.c)
add_test(NAME web_request COMMAND web_request)

# cleanup
add_test(NAME curl_cleanup COMMAND rm curl.html)

# set fixtures
set_tests_properties(web_request PROPERTIES FIXTURES_REQUIRED web_request)
set_tests_properties(curl_setup PROPERTIES FIXTURES_SETUP web_request)
set_tests_properties(curl_cleanup PROPERTIES FIXTURES_CLEANUP web_request)

# Check if web_request accepts http and https, and refuses other protocols
add_test_executable(imc::libfetch web_request_errors web_request/web_request_errors.test.c)
add_test(NAME web_request_errors COMMAND web_request_errors)

### Hash ###

# test hash validation
add_test_executable(imc::libfetch hash_validation hash/hash_validation.test.c)
add_test(NAME hash_validation COMMAND hash_validation)

# test hash comparison
add_test_executable(imc::libfetch hash_comparison hash/hash_comparison.test.c)
add_test(NAME hash_comparison COMMAND hash_comparison)

# test hash calculation
add_test_executable(imc::libfetch hash_calculation hash/hash_calculation.test.c)
add_test(NAME hash_calculation COMMAND hash_calculation)

# fixtures for comparison
set_tests_properties(hash_comparison PROPERTIES FIXTURES_REQUIRED requires_hash_validation)
set_tests_properties(hash_validation PROPERTIES FIXTURES_SETUP requires_hash_validation)

# fixtures for calculation
set_tests_properties(hash_calculation PROPERTIES FIXTURES_REQUIRED requires_hash_comparison)
set_tests_properties(hash_comparison PROPERTIES FIXTURES_SETUP requires_hash_comparison)
