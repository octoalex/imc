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

from manifest.versions import get_manifest
from manifest.destructure import destructure
from os.path import join
from json import loads, dumps

# check both the main manifest and the various version specifics for duplicated data


def get_redundant_fields(manifest_version: dict, version: dict) -> set:
    redundancies = set()
    for key in manifest_version.keys():
        if key in version.keys() and version[key] == manifest_version[key]:
            redundancies.add(key)
    return redundancies


def get_all_redundant_fields(cache_dir) -> set:
    manifest = get_manifest()
    redundancies: set|None = None
    for manifest_version in manifest["versions"]:
        with open(join(cache_dir, f"{manifest_version["id"]}.json"), "r") as file:
            version = loads(file.read())
        version_redundancies = get_redundant_fields(manifest_version, version)
        if redundancies is None:
            redundancies = version_redundancies
        else:
            redundancies.intersection_update(version_redundancies)
    return redundancies


def command_redundancies(cache_dir, output_dir):
    redundant = get_all_redundant_fields(cache_dir)
    print("Redundancies found!")

    data = dumps(sorted(e for e in redundant), indent=2)
    path = join(output_dir, "redundancies.json")
    with open(path, "w") as file:
        file.write(data)

    print(f"Data written to {path}")