#pragma once

#include "../utils/utils.h"

void init_alloc();

void* my_malloc(size_t _Size);

void* my_realloc(void* _Block, size_t _Size);

void* my_calloc(size_t _Count, size_t _Size);

void my_free(void* _Block);