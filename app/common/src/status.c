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

#include <stdlib.h>

bool is_status_success(const status status) {
    return status.code == STATUS_SUCCESSFUL_CODE;
}

void free_status(status *status) {
    free(status->message);
    status->message = nullptr;
    status->code = STATUS_NULL_CODE;
}

void free_status_unsafe(const status status) {
    free(status.message);
}
