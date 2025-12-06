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

from re import compile
from manifest.versions import get_manifest
from manifest.common import merge, print_progress_bar
from os.path import join
from json import loads, dumps

URL_PATTERN = compile(
    "https?://[a-zA-Z0-9\\-_]+(\\.[a-zA-Z0-9\\-_]+)*((/[a-zA-Z0-9\\-_.]+)*/?(\\?[a-zA-Z0-9\\-_.]+=[a-zA-Z0-9\\-_.]+(&[a-zA-Z0-9\\-_.]+=[a-zA-Z0-9\\-_.]+)*)?)?"
)

RELEASE_PATTERN_STR = "(1|(2[6-9])|([3-9][0-9]))(\\.[1-9][0-9]?){1,2}(-(((pre)|(rc))[1-4]))?"
SNAPSHOT_PATTERN_STR = "(1[3-9])|([2-9][0-9])w((0[1-9])|([2-4][0-9])|(5[0-3]))[a-z]"
VERSION_PATTERN = compile(f"^(({RELEASE_PATTERN_STR})|({SNAPSHOT_PATTERN_STR}))$")
SHA1_PATTERN = compile("^([0-9a-f]{40})$")
NUMBER_PATTERN = compile("^([0-9]+)$")

def destructure(origin):
    if type(origin) == str:
        if URL_PATTERN.match(origin):
            return "url"
        elif VERSION_PATTERN.match(origin):
            return "version"
        elif SHA1_PATTERN.match(origin):
            return "sha1"
        elif NUMBER_PATTERN.match(origin):
            return "index"
        else:
            return "str"
    elif type(origin) == dict:
        destructured = dict()
        for k in origin.keys():
            destructured[k] = destructure(origin[k])
        return destructured
    elif type(origin) == list:
        destructured = []
        for e in origin:
            se = destructure(e)
            if se not in destructured:
                destructured.append(se)
        return sorted(destructured, key=lambda x: type(x).__name__)
    else:
        return type(origin).__name__


def command_destructure(cache_dir, output_dir, version):
    manifest = get_manifest()
    print("Analysing structure")
    path = join(output_dir, f"{version}.json")

    if version in { "release", "snapshot" }:
        section = "latest"
    elif version == "latest":
        section = "latest"
        version = "release"
    else:
        section = "versions"
    with open(join(cache_dir, f"{manifest[section][version]}.json"), "r") as file:
        data = loads(file.read())
        base = destructure(data)
    print("Structure analyzed")

    string = dumps(base, sort_keys=True, indent=2)
    with open(path, "w") as file:
        file.write(string)

    print(f"Data written to {path}")
