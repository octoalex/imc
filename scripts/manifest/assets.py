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
from os.path import join
from json import loads, dumps


def check_asset_index_redundancy(version: dict) -> bool:
    try:
        return version["assetIndex"]["id"] == version["assets"]
    except KeyError:
        return False


def get_redundant_assets(cache_dir) -> set:
    manifest = get_manifest()
    failed = set()
    for manifest_version in manifest["versions"]:
        with open(join(cache_dir, f"{manifest_version["id"]}.json"), "r") as file:
            version = loads(file.read())
        if not check_asset_index_redundancy(version):
            failed.add(manifest_version["id"])
    return failed


def command_assets(cache_dir, output_dir):
    missing = get_redundant_assets(cache_dir)
    print("Asset Index analyzed!")

    data = dumps(sorted(e for e in missing), indent=2)
    path = join(output_dir, "asset_index.json")
    with open(path, "w") as file:
        file.write(data)

    print(f"Data written to {path}")