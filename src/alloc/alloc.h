#pragma once

#include "../utils/utils.h"


#define BLOCK_SIZE 4096
#define START_PTR (size_t*)0x100000
#define END_PTR (size_t*)0x400000

void init_alloc();

void* kernel_malloc(size_t _Size);

void* kernel_realloc(void* _Block, size_t _Size);

void* kernel_calloc(size_t _Count, size_t _Size);

void kernel_free(void* _Block);