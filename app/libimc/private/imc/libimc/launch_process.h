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

#ifndef IMC_LAUNCH_PROCESS_H
#define IMC_LAUNCH_PROCESS_H

#include <stdio.h>

#ifdef linux
#   include <unistd.h>
#elifdef _WIN32
#   include <processthreadsapi.h>
#endif

constexpr pid_t PROCESS_ERROR_NULL_COMMAND = -1;
constexpr pid_t PROCESS_ERROR_PROGRAM_DOES_NOT_EXISTS = -2;
constexpr pid_t PROCESS_ERROR_PROGRAM_CANNOT_BE_EXECUTED = -3;
constexpr pid_t PROCESS_ERROR_WORKING_DIRECTORY_INVALID = -4;
constexpr pid_t PROCESS_ERROR_CREATION_FAIL = -5;

#ifdef _WIN32

typedef DWORD pid_t;

#endif

/// Launches a process
/// @param command The command to execute, including the arguments                                                  <br>
///   First argument is the executable, and it must be the relative or absolute path to the executable              <br>
///   Must be null terminated
/// @param working_directory The directory where the process is launched                                            <br>
///   If null, then the current working directory will be used
/// @param in The process's standard input                                                                          <br>
///   If null, then the current standard input will be used
/// @param out The process's standard output                                                                        <br>
///   If null, then the current standard output will be used
/// @param err The process's standard error                                                                         <br>
///   If null, then the current standard error will be used
/// @return Either the process's PIC, or an error code                                                              <br>
///   Error codes:
///     - -1: Empty command
///     - -2: Program does not exist
///     - -3: Process is inaccessible, or cannot be executed
///     - -4: Working directory is not accessible
///     - -5: Process creation failed
/// @bug On Linux, all the calling process's file descriptors are kept by the launched process
pid_t launch_process(const char *command[], const char *working_directory, FILE *in, FILE *out, FILE *err);

/// Waits for the process to terminate, and returns its exit code
/// @param process The process's PID                                                                                <br>
///   If the pid is an error value, then the function will return 0
/// @param was_killed Whether the process exited normally (by the main returning or calling exit)                   <br>
///   If null, then it will be ignored
/// @return The process's exit code
int wait_process(pid_t process, bool *was_killed);

/// Check if the process is still alife
/// @param process The process's PID                                                                                <br>
///   If the pid is an error value, then the function will return false
/// @return Whether the process is still running
bool is_process_alive(pid_t process);

#endif //IMC_LAUNCH_PROCESS_H