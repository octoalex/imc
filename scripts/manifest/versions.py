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
from os.path import join, isfile
from manifest.common import verify_directory, print_progress_bar
from requests import get
from json import loads


VERSION_MANIFEST_URL = "https://launchermeta.mojang.com/mc/game/version_manifest.json"
TIMESTAMP_KEY = "releaseTime"
SPECIAL_VERSIONS = { "latest", "release", "snapshot" }

manifest_cache = None
versions_cache = None


def _update_version(version: dict, cache_directory: str):
    remote = get(version["url"])
    path = join(cache_directory, f"{version["id"]}.json")
    with open(path, "w") as file:
        file.write(remote.text)


def get_manifest() -> dict:
    global manifest_cache
    if manifest_cache is None:
        manifest_cache = get(VERSION_MANIFEST_URL).json()
    return manifest_cache


def update_caches(cache_directory: str):
    verify_directory(cache_directory)
    print("Updating Caches")
    manifest = get_manifest()
    version_count = len(manifest["versions"])
    i = 1

    print(f"Checking {version_count} versions")

    for version in manifest["versions"]:
        v_id = version["id"]
        prompt = f"({i}/{version_count}) Version {v_id}\t".expandtabs(16)
        frac = float(i) / version_count
        i += 1

        print_progress_bar(prompt, frac)

        path = join(cache_directory, f"{v_id}.json")

        if not isfile(path):
            _update_version(version, cache_directory)
            continue

        new_timestamp = version[TIMESTAMP_KEY]
        old_timestamp = ""
        with open(path, "r") as file:
            old_timestamp = loads(file.read())[TIMESTAMP_KEY]
        if old_timestamp != new_timestamp:
            _update_version(v_id, cache_directory)

    print_progress_bar(f"({version_count}/{version_count}) All done!\t\t".expandtabs(16), 1)
    print()
    print("Caches updated!")


def is_version_valid(version: str) -> bool:
    global versions_cache
    if versions_cache is None:
        versions_cache = set()
        for v in get_manifest()["versions"]:
            versions_cache.add(v["id"])
    return version in versions_cache or version in SPECIAL_VERSIONS
