// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Licensed under the Apache License, Version 2.0 (See accompanying
// file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app-eu/ncc

.text

// Please compile using the intel synta support.
// Any PR trying to 'fix' this will get closed.

.globl __nrt_palloc_;
.globl __nrt_pfree_;

.globl __nrt_pthread_new_;
.globl __nrt_pthread_kill_;

#ifdef __x86_64__
#include "Platform/__x86_64__.s"
#endif
