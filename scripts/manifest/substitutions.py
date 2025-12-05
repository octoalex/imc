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
from manifest.common import print_progress_bar
from os.path import join
from json import loads, dumps
from re import compile


SUBSTITUTION_PATTERN = compile("(-D[a-zA-Z_.]+=)?\\$\\{[a-z_]+}")


def get_substitution_key(raw: str) -> str:
    start = raw.find("${")
    end = raw.find("}", start)
    return raw[start + 2:end]


def find_substitutions(argument: str | dict | list) -> set|str:
    if type(argument) == dict:
        return find_substitutions(argument["value"])
    elif type(argument) == list:
        base = set()
        for e in argument:
            found = find_substitutions(e)
            if type(found) == set:
                base.update(found)
            else:
                base.add(found)
        return base
    elif SUBSTITUTION_PATTERN.match(argument):
            return get_substitution_key(argument)

    return set()


def command_substitutions(cache_dir, output_dir):
    manifest = get_manifest()

    base = dict[str, set]()
    base["legacy"] = set()
    version_count = len(manifest["versions"])
    i = 1
    for version in manifest["versions"]:
        prompt = f"({i}/{version_count}) Version {version["id"]}\t".expandtabs(16)
        print_progress_bar(prompt, float(i) / version_count)
        with open(join(cache_dir, f"{version["id"]}.json"), "r") as file:
            data = loads(file.read())
        try:
            for category in data["arguments"].keys():
                if category not in base.keys():
                    base[category] = set()
                base[category].update(find_substitutions(data["arguments"][category]))
        except KeyError:
            for argument in data["minecraftArguments"].split(" "):
                if SUBSTITUTION_PATTERN.match(argument):
                    base["legacy"].add(get_substitution_key(argument))
        i += 1

    print_progress_bar(f"({version_count}/{version_count}) All done!\t\t".expandtabs(16), 1)
    string = dumps({k: [e for e in base[k]] for k in base.keys()}, sort_keys=True, indent=2)
    path = join(output_dir, "substitutions.json")
    with open(path, "w") as file:
        file.write(string)
    print(f"Data written to {path}")
