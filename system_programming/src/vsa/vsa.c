
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      10.05.2020               **
**  Reviewer:  Amir David				**
**  Status:    in progress				**
*****************************************/	

#include <stddef.h>	/* for size_t */

#include "vsa.h"

#define WORD 8		/* length of machine word */

struct vsa
{
	long size;		 
	#ifndef NDEBUG
	vsa_t *pool;
	#endif
};

/*					
	each offset holds the size of its block (positive for allocated, 
											 negative for free) 
											 					
					 ______________________
					|_____size__1__________|_____<-- offset / size
					|					   |
					|					   |
					|		block 1		   |
					|					   |
					|______________________|_____
					|_____size__2__________|_____<-- offset / size
					|					   |
					|					   |
					|		block 2		   |
					|					   |
					|______________________|_____
					|_____size__3__________|_____<-- offset / size
					|					   |
					|		block 3		   |
								.
								.
								.
					|______________________|
					|______END = NULL______|
								
*/
/*----------------------------------------------------------------------------*/
/* 
O(1) 
init memory pool. return pointer to pool begin
*/
vsa_t *VSAInit(void *mem_segment, size_t size)

	/*define pool struct at begining of mem_segment*/
	vsa_t *pool = (vsa_t *)mem_segment;
	
	block_t *blk = NULL;
	size_t offset_iter = 0;
	
	assert(NULL != mem_segment);
			
	/*next_free points to next block wihle alligned*/
	pool->next_free = sizeof(vsa_t);
	pool->block_size = sizeof(block_t) + (((block_size - 1)/WORD + 1) * WORD);	;
	pool->num_blocks = (size - sizeof(vsa_t))/ pool->block_size;		
		
	for(offset_iter = pool->next_free; 
		offset_iter < size; 
		offset_iter += pool->block_size)
	{		
		blk = (block_t *)((char *)pool + offset_iter);

		blk->offset = offset_iter + pool->block_size;
		#ifdef DEBUG
		blk->pool = pool;
		#endif
	}

	/*change lasts blocks offset to 0*/
	blk->offset = 0;
	
	return (pool);


/*----------------------------------------------------------------------------*/
/*
O(n) 
allocate memory block 
* combines adjacent free blocks
*/
void *VSAAlloc(vsa_t *pool, size_t size_to_alloc);


/*----------------------------------------------------------------------------*/
/*
O(1) 
free block
*/
void VSAFree(void *chunk);


/*----------------------------------------------------------------------------*/
/*
O(n) 
Return the largest chunk 
* combines adjacent free blocks
*/
size_t VSALargestChunkAvailable(vsa_t *pool);

