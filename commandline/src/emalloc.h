#ifndef EMALLOC_H
#define EMALLOC_H

#include <stdlib.h>

extern void *emalloc(size_t bytes);

extern void *erealloc(void *ptr, size_t bytes);

extern void *ecalloc(int num, size_t bytes);

#endif
