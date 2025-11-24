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

#ifdef linux

#include <dirent.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <imc/libimc/launch_process.h>
#include <sys/stat.h>
#include <sys/wait.h>

static void close_all_file_descriptors();

pid_t launch_process(const char *command[], const char *working_directory, FILE *in, FILE *out, FILE *err) {
    // CHECKS

    // check that there is a command
    if (command == nullptr || *command == nullptr) {
        return PROCESS_ERROR_NULL_COMMAND;
    }

    // check that the program exists
    if (access(*command, F_OK) != 0) {
        return PROCESS_ERROR_PROGRAM_DOES_NOT_EXISTS;
    }

    // check that the program can be executed
    if (access(*command, R_OK | X_OK) != 0) {
        return PROCESS_ERROR_PROGRAM_CANNOT_BE_EXECUTED;
    }

    // check that the working directory is valid
    struct stat st;
    if (working_directory != nullptr && (
        stat(working_directory, &st) != 0 || !S_ISDIR(st.st_mode))
        ) {
        return PROCESS_ERROR_WORKING_DIRECTORY_INVALID;
    }

    // checks completed, launch the process

    const pid_t process = fork();

    if (process < 0) {
        return PROCESS_ERROR_CREATION_FAIL;
    } else if (process == 0) {
        if (working_directory != nullptr) {
            chdir(working_directory);
        }

        if (in != nullptr && in != stdin) {
            const int in_fileno = fileno(in);
            dup2(in_fileno, STDIN_FILENO);
        }

        if (out != nullptr && out != stdout) {
            const int out_fileno = fileno(out);
            dup2(out_fileno, STDOUT_FILENO);
        }

        if (err != nullptr && err != stderr) {
            const int err_fileno = fileno(err);
            dup2(err_fileno, STDERR_FILENO);
        }
        // close all other file pointers
        // closing them before copying them will lead to bugs!
        // (there is a reason this was written here)
        close_all_file_descriptors();

        execv(*command, (char * const*)command);
    }
    return process;
}

int wait_process(pid_t process, bool *was_killed) {
    if (process <= 0) {
        return 0;
    }

    siginfo_t status;
    waitid(P_PID, process, &status, WEXITED | WSTOPPED);

    if (was_killed != nullptr) {
        *was_killed = status.si_code != CLD_EXITED;
    }
    return status.si_status;
}

bool is_process_alive(pid_t process) {
    if (process <= 0) {
        return 0;
    }

    return kill(process, 0) == 0;
}

// Helpers

static void close_all_file_descriptors() {
    pid_t self_pid = getpid();
    size_t path_size = 6 /* /proc/ */
        + (int) ceil(log(self_pid + 1)) /* the pid's length in characters */
        + 4 /* /fd/ */
        + 1 /* the termination character */;

    char fd_path[path_size];
    sprintf(fd_path, "/proc/%d/fd/", self_pid);

    struct dirent *entry;

    // Code based on the one found at https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html
    DIR* dp = opendir(fd_path);
    if (dp != nullptr) {
        while ((entry = readdir (dp))) {
            char *error;
            int fd = (int)strtol(entry->d_name, &error, 10);
            // a simple fd < 3 could do, but I prefer this approach, as IMO it makes it clearer that I'm only checking
            // for those fds
            if (error == entry->d_name
                || fd == STDIN_FILENO
                || fd == STDOUT_FILENO
                || fd == STDERR_FILENO
                ) {
                // either the file is not numeric, thus not an FD,
                // or it's a reserved fd (stdin, stdout, stderr) and thus should not be closed
                // thus, it's skipped
                continue;
            }
            // close the fd
            close(fd);
        }
        closedir(dp);
    }
}

#endif
