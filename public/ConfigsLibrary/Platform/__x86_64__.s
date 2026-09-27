// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app-eu/ncc

.text

/// @brief These files take care of allocation and mgmt.

.extern __nrt_p_new_region
.extern __nrt_p_free_region
.extern __nrt_p_new_thread
.extern __nrt_p_kill_thread

__nrt_palloc_:
    push rax
    push rcx
    call __nrt_p_new_region
    pop rcx
    mov rdx, rax
    pop rax
    ret

__nrt_pfree_:
    push rax
    push rcx
    call __nrt_p_free_region
    pop rcx
    mov rdx, rax
    pop rax
    ret

__nrt_pthread_new_:
    push rax
    push rcx
    call __nrt_p_new_thread
    pop rcx
    mov rdx, rax
    pop rax
    ret

__nrt_pthread_kill_:
    push rax
    push rcx
    call __nrt_p_kill_thread
    pop rcx
    mov rdx, rax
    pop rax
    ret
