#pragma once

typedef void* va_list;

#define va_start(list, paramN) \
list = (char*)&(paramN) + sizeof(&(paramN));

#define va_arg(list, type) \
*(type*)(list); \
list = (char*)((list) + sizeof(type*));

#define va_end(list) ((list) = (void*)0)

typedef unsigned int size_t;

void memcpy(void *dest, const void *src, size_t size);

void memset(void *dest, char ch, size_t count);