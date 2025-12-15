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
add_test(NAME create_base_directory COMMAND mkdir dir)
add_test(NAME create_files COMMAND touch accessible inaccessible)
add_test(NAME file_access_all COMMAND chmod 777 accessible)
add_test(NAME file_access_none COMMAND chmod 000 inaccessible)

# Test is_dir
add_test_executable(imc::libcommon is_dir file_utils/is_dir.test.c)
add_test(NAME is_dir COMMAND is_dir)

# Test is_file
add_test_executable(imc::libcommon is_file file_utils/is_file.test.c)
add_test(NAME is_file COMMAND is_file)

# Test can_read
add_test_executable(imc::libcommon can_read file_utils/can_read.test.c)
add_test(NAME can_read COMMAND can_read)

# Test can_write
add_test_executable(imc::libcommon can_write file_utils/can_write.test.c)
add_test(NAME can_write COMMAND can_write)

# Test can_execute
add_test_executable(imc::libcommon can_execute file_utils/can_execute.test.c)
add_test(NAME can_execute COMMAND can_execute)

# cleanup
add_test(NAME cleanup_files COMMAND rm -rf dir accessible inaccessible)

# set fixtures
set_tests_properties(is_dir is_file can_read can_write can_execute PROPERTIES FIXTURES_REQUIRED file_utils)
set_tests_properties(
        create_base_directory create_files file_access_all file_access_none
        PROPERTIES FIXTURES_SETUP file_utils
)
set_tests_properties(cleanup_files PROPERTIES FIXTURES_CLEANUP file_utils)

### make_dirs ###

# setup for make_dirs
add_test(NAME make_dirs_setup COMMAND mkdir a a/b)

# test make_dirs
add_test_executable(imc::libcommon make_dirs file_utils/make_dirs.test.c)
add_test(NAME make_dirs COMMAND make_dirs)

# cleanup make_dirs
add_test(NAME make_dirs_cleanup COMMAND rm -r a e)

# set fixtures for make_dirs
set_tests_properties(make_dirs PROPERTIES FIXTURES_REQUIRED make_dirs)
set_tests_properties(make_dirs_setup is_dir PROPERTIES FIXTURES_SETUP make_dirs)
set_tests_properties(make_dirs_cleanup PROPERTIES FIXTURES_CLEANUP make_dirs)

##############
##############
##############
 ###      ###
 ### Pipe ###
 ###      ###
 ###      ###
 ###      ###

add_test_executable(imc::libcommon pipe pipe/pipe.test.c)
add_test(NAME pipe COMMAND pipe)
set_tests_properties(pipe PROPERTIES TIMEOUT 3)
