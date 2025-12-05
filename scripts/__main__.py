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

from sys import argv
from os.path import join
from manifest.common import verify_directory
from manifest.versions import update_caches, is_version_valid
from manifest.destructure import command_destructure
from manifest.substitutions import command_substitutions
from manifest.redundancies import command_redundancies


CACHE_SUBDIR = "cache"
OUTPUT_SUBDIR = "generated"


if len(argv) < 2:
    print("No command was specified!")
    exit(-1)
elif len(argv) == 2 and argv[1] == "help":
    print("imc developer utils, version 1.0.0")
    print("Available commands:")
    print("\t- destructure <build_directory> <game_version>")
    print("\t- substitutions <build_directory>")
    print("\t- help")
    exit(0)
elif len(argv) < 3:
    print("No build directory was specified!")
    exit(-1)

command = argv[1]
build_dir = argv[2]
cache_dir = join(build_dir, CACHE_SUBDIR, "manifests")
output_dir = join(build_dir, OUTPUT_SUBDIR, "manifests")

update_caches(cache_dir)
verify_directory(output_dir)

match command:
    case "destructure":
        if len(argv) < 4:
            print("Command destructure requires additional version argument!")
            exit(-1)
        version = argv[3]
        if not is_version_valid(version):
            print("Version", version, "does not exist!")
            exit(-1)
        command_destructure(cache_dir, output_dir, version)
    case "substitutions":
        command_substitutions(cache_dir, output_dir)
    case "redundancies":
        command_redundancies(cache_dir, output_dir)
    case _:
        print("Invalid command ", command)
        exit(-1)
