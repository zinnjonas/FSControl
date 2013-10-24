#include <stdlib.h>
#include <stdio.h>

#include "emalloc.h"

void *emalloc(size_t bytes)
{
    void *mem = malloc(bytes);

    if(!mem)
    {
        printf("Could not allocate %zd byte of memory. "
               "Terminating!\n", bytes);
        exit(EXIT_FAILURE);
    }

    return mem;
}


void *erealloc(void *ptr, size_t bytes)
{
    void *mem = realloc(ptr, bytes);

    if(!mem)
    {
        printf("Could not reallocate %zd byte of memory. "
               "Terminating!\n", bytes);
        exit(EXIT_FAILURE);
    }

    return mem;
}

void *ecalloc(int num, size_t bytes)
{
    void *mem = calloc(num, bytes);

    if(!mem)
    {
        printf("Could not allocate %zd byte of memory. "
               "Terminating!\n", bytes);
        exit(EXIT_FAILURE);
    }

    return mem;
}

