/* 
 * This file is part of octoalex's imc (https://github.com/octoalex/imc).
 * Copyright (c) 2025 octoalex.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Created by octoalex on 22/11/2025.
 */

#ifndef IMC_CONFIG_IN_H
#define IMC_CONFIG_IN_H

const char *const PROJECT_NAME = "@CMAKE_PROJECT_NAME@";

constexpr int VERSION_MAJOR = @imc_VERSION_MAJOR@;
constexpr int VERSION_MINOR = @imc_VERSION_MINOR@;
constexpr int VERSION_PATCH = @imc_VERSION_PATCH@;

const char *const COMPILER_ID = "@CMAKE_C_COMPILER_ID@";

const char *const SYSTEM_NAME = "@CMAKE_SYSTEM_NAME@";

#endif //IMC_CONFIG_IN_H