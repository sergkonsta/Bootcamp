#ifndef __OL87_VSA_H__
#define __OL87_VSA_H__


#include <stddef.h>	/* for size_t */
/*
struct vsa
{
	long size; 
	#ifndef NDEBUG
	long magic;
	#endif
};
*/

typedef struct vsa vsa_t;


/* O(1) Initiate fixed size memory pool 
	ptr points to first address in block
	size - size of segment
	block_size
	return pool struct */
vsa_t *Init(void *mem_segment, size_t size);

/*O(n) allocate 1 block_size */
void *Alloc(vsa_t *pool, size_t size_to_alloc);

/*O(1) free block*/
void Free(void *chunk);

/*O(n) Return number of free blocks in mem_pool */
size_t LargestChunkAvailable(vsa_t *pool);




#endif /*  __OL87_VSA_H__ */
