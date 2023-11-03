#pragma once

#include "../utils/utils.h"

void init_alloc();

void* kernel_malloc(size_t _Size);

void* kernel_realloc(void* _Block, size_t _Size);

void* kernel_calloc(size_t _Count, size_t _Size);

void kernel_free(void* _Block);