#ifndef __OL87_VSA_H__
#define __OL87_VSA_H__


#include <stddef.h>	/* for size_t */

typedef struct vsa vsa_t;

/* 
O(1) 
init memory pool. return pointer to pool begin
*/
vsa_t *VSAInit(void *mem_segment, size_t size);

/*
O(n) 
allocate memory block 
* combines adjacent free blocks
*/
void *VSAAlloc(vsa_t *pool, size_t size_to_alloc);

/*
O(1) 
free block
*/
void VSAFree(void *chunk);

/*
O(n) 
Return the largest chunk 
* combines adjacent free blocks
*/
size_t VSALargestChunkAvailable(vsa_t *pool);


#endif /*  __OL87_VSA_H__ */
