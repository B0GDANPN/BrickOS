#include "alloc.h"
#include "../utils/utils.h"


static size_t* head;

void init_alloc() {
	
	head = START_PTR;
    size_t* ptr = START_PTR;
	size_t step = BLOCK_SIZE / sizeof(size_t);
	while (ptr < END_PTR) {
		*ptr = (size_t)(ptr + step);
        ptr += step;
    }
	*ptr = NULL;
}

void* kernel_malloc(size_t _Size) {
	if (_Size  > BLOCK_SIZE)
		return NULL;
	size_t* buff = head;
	head = (size_t*)*head;
	return (void*)buff;
}

void* kernel_realloc(void* _Block, size_t _Size) {
	if (_Size > BLOCK_SIZE)
		return NULL;
	if (_Block == NULL)
		return kernel_malloc(_Size);
	return _Block;
}

void* kernel_calloc(size_t _Count, size_t _Size) {
	void* ptr = kernel_malloc(_Count * _Size);
	memset(ptr, 0, _Count);
	return ptr;
}

void kernel_free(void* _Block) {
	size_t* buff = (size_t*)_Block;
	*buff = (size_t)head;
	head = buff;
}