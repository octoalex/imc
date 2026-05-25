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
 * Created by octoalex on 30/12/2025.
 */

#include <imc/common/status.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

const status STATUS_ERROR_OUT_OF_MEMORY = {
    .code = 0x0000'0010,
    .message = "Program has run out of memory"
};

const status STATUS_ERROR_FILE_NOT_FOUND = {
    .code = 0x0000'0011,
    .message = "File \"%s\" could not found"
};

static const status STATUS_ERROR_CANNOT_FREE_NON_RUNTIME_STATUS = {
    .code = 0x1111'1110,
    .message = "Status %p cannot be freed, since it was not created by create_status"
};

bool is_status_success(const status *status) {
    return status->code == STATUS_SUCCESSFUL_CODE;
}

status *create_status(const int code, const char *NULLABLE format, ...) {
    status *s = calloc(1, sizeof(status));
    s->code = code;
    s->allocated_at_runtime = true;

    if (format != nullptr) {
        va_list list;
        va_list discover;
        va_start(list, format);
        va_copy(discover, list);

        const size_t size = vsnprintf(nullptr, 0, format, discover);
        s->message = calloc(size + 1, sizeof(char));
        vsprintf(s->message, format, list);
    }

    return s;
}

void free_status(status *status) {
    if (status == nullptr) {
        return;
    }
    if (!status->allocated_at_runtime) {
        struct status *err = create_status(
            STATUS_ERROR_CANNOT_FREE_NON_RUNTIME_STATUS.code,
            STATUS_ERROR_CANNOT_FREE_NON_RUNTIME_STATUS.message, status);
        error(err);
        free_status(err);
    }
    free(status->message);
    status->message = nullptr;
    status->code = STATUS_NULL_CODE;
    free(status);
}

void free_status_unsafe(status status) {
    free_status(&status);
}

void error(const status *status) {
    if (status->code == 0) return;
    fprintf(stderr, "Error #%x", status->code);
    if (status->message != nullptr) {
        fprintf(stderr, ": \"%s\"", status->message);
    }
    fprintf(stderr, "\n");
    exit(status->code);
}

void warn(const status *status) {
    if (status->code == 0) return;
    fprintf(stderr, "Warning #%x", status->code);
    if (status->message != nullptr) {
        fprintf(stderr, ": \"%s\"", status->message);
    }
    fprintf(stderr, "\n");
}
