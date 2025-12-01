#include <stdint.h>
#include <stddef.h> 
#include "utils.h"
#include "allocator.h"

#define SIMPLE_MALLOC_BUFFER_SIZE 16384
static unsigned char simple_malloc_buffer[SIMPLE_MALLOC_BUFFER_SIZE];
static size_t simple_malloc_offset = 0;

void* simple_malloc(size_t size)
{
    size_t  size_aligned = (size_t) utils_align_up((unsigned long)size, 8);

    if((simple_malloc_offset + size_aligned) > SIMPLE_MALLOC_BUFFER_SIZE)
    {
        return NULL; // not enough space
    }
    else
    {
        void* allocated = (void *) &simple_malloc_buffer[simple_malloc_offset];
	    simple_malloc_offset += size_aligned ;
        return allocated;
    }
    

}