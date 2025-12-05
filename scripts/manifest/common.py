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

from os.path import isdir
from os import makedirs
from shutil import get_terminal_size


PROGRESS_BAR_FIXED_CHAR_COUNT = 4


def merge(new: dict|str, base: dict|list[str]):
    if type(new) == dict:
        for key in new.keys():
            if key not in base:
                if type(new[key]) == dict:
                    base[key] = dict()
                else:
                    base[key] = list()
            merge(new[key], base[key])
    else:
        if new not in base:
            base.append(new)


def verify_directory(directory: str):
    if not isdir(directory):
        makedirs(directory)


def print_progress_bar(prompt, frac):
    width = get_terminal_size((120, 0)).columns - len(prompt) - PROGRESS_BAR_FIXED_CHAR_COUNT
    progress = round(frac * width)
    print("\r", prompt, "[ ", "#" * progress, "-" * (width - progress), " ]", sep="", end="")