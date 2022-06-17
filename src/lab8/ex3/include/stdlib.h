#ifndef STDLIB_H
#define STDLIB_H

#include "os_type.h"

template<typename T>
void swap(T &x, T &y);

void itos(char *numStr, uint32 num, uint32 mod);

void memset(void *memory, char value, int length);

int ceil(const int dividend, const int divisor);
#endif
