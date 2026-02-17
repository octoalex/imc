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
 * Created by octoalex on 15/12/2025.
 */

#ifndef IMC_PIPE_H
#define IMC_PIPE_H

#include <stdio.h>

/// Creates 2 file descriptors: what's written in write will be readable from read
/// @param read The read end of the pipe, like a file opened with @code fopen(path, "r")@endcode
/// @param write The write end of the pipe, like a file opened with @code fopen(path, "w")@endcode
/// @note The default buffering mode is not specified. If you want to be sure to have line buffering, run the following
///       code <b>before</b> doing any read or write operations on either <br/>
///       @code setlinebuf(write /* or read */);@endcode <br/>
///       For more information, look at
///       <a href="https://manpages.debian.org/trixie/manpages-dev/setvbuf.3.en.html"> `setvbuf`'s manpage </a>
/// @return Whether the pipe creation was successful
bool create_pipe(FILE **read, FILE **write);

#endif //IMC_PIPE_H
