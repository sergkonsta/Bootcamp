
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      10.05.2020               **
**  Reviewer:  Amir David				**
**  Status:    in progress				**
*****************************************/	

#include <stddef.h>		/*for size_t*/
#include <assert.h>		/*for assert*/

#include "vsa.h"

#define ABS(x) ((x < 0) ? ((-1) * x) : x)

#define WORD_SIZE (sizeof(size_t))
#define META_SIZE (sizeof(vsa_t))

#define FREE (-1)

#define NEXT_BLOCK(x) ((vsa_t *)((size_t)x + META_SIZE + (size_t)ABS(x->size)))



struct vsa
{
	long size;		 
	#ifndef NDEBUG
	long tag; /*verification that chunk is from this pool*/
	#endif
};

static void MergeAdjacentFree(vsa_t *header);

/*					
	each offset holds the size of its block (positive for allocated, 
											 negative for free) 
											 					
	vsa_t *------->	 ______________________
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
					|_____FOOTER = 0_______|
								
*/
/*----------------------------------------------------------------------------*/
/* 
O(1) 
init memory pool. 
return pointer to pool begin
or null if not enough size.
*/
vsa_t *VSAInit(void *mem_segment, size_t size)
{
	/*typecast empty memory pool*/
	vsa_t *block = (vsa_t *)mem_segment;
	
	assert(NULL != mem_segment);

	/*whether size is big enough*/
	if(size < 2 * META_SIZE + WORD_SIZE)
	{
		return NULL;
	}	
	
	/* size machine word alignment */
	size -= size % WORD_SIZE;
	
	/*first block size: header + room for data (not including space for footer) 
	negative for free block	*/
	block->size = (long)(FREE * (size - 2 * META_SIZE));
	
	/*define the footer*/ 
	block = NEXT_BLOCK(block);
	block->size = 0;
	
	return ((vsa_t *)mem_segment);
}


/*----------------------------------------------------------------------------*/
/*
O(n) 
allocate memory block 

* combines adjacent free blocks

returns null if no space found
*/
void *VSAAlloc(vsa_t *pool, size_t size_to_alloc)
{
	vsa_t *block = pool;
	long free_block_size = 0;
	void *ret = NULL;
	
	assert(pool);

	size_to_alloc += (WORD_SIZE - size_to_alloc % WORD_SIZE) % WORD_SIZE;


	while(0 != block->size)
	{
		MergeAdjacentFree(block);

		/* if chunk of asked size */
		if((long)(size_to_alloc + META_SIZE) <= ABS(block->size))	
		{
			/* holds original size of free chunk - negative value*/
			free_block_size = block->size;
			
			/*hold return value - pointer to allocated space*/
			ret = (void *)((size_t)block + META_SIZE);

			/*initialize meta-data*/
			block->size = (long)size_to_alloc;
			#ifndef NDEBUG
			block->tag = 0xDEADBEEF;
			#endif
			
			/*update block after allocation*/
			block = NEXT_BLOCK(block);		
			block->size = 
			free_block_size + (long)size_to_alloc + (long)META_SIZE;
			
			return ret;
		}
		
		/* advance to next chunk, current can't be allocated (small/occupied) */
		block = NEXT_BLOCK(block);	
	}


	/* if chunk with suitable size wasn't found */
	return NULL;
}


/*----------------------------------------------------------------------------*/
/*
O(1) 
free block
*/
void VSAFree(void *chunk)
{
	vsa_t *block = NULL;

	assert(chunk);

	/* get pointer to header */
	block = (vsa_t *)((size_t)chunk - META_SIZE);

	assert(block->tag == 0xDEADBEEF);
	assert(block->size > 0);

	/* change header status to free */
	block->size = FREE * block->size;
	
	return;
}


/*----------------------------------------------------------------------------*/
/*
O(n) 
Return the largest chunk 
* combines adjacent free blocks

alg:
iter through pool until pool->size == 0

if size is negative and bigger than saved size - increase it
*/
size_t VSALargestChunkAvailable(vsa_t *pool)
{
	size_t result = 0;
	vsa_t *block = pool;
	
	assert (NULL != pool);	
	
	/*while end of pool isn't reached*/
	while(0 != block->size)
	{
		/*check for adjacent free blocks and merge */
		MergeAdjacentFree(block);			
		

		/*save bigger chunk if found*/
		if(result < (size_t)(block->size))
		{
			result = ABS(block->size);
		}
		
		/* advance to next heder */
		block = NEXT_BLOCK(block);	
	}
	
	return (result);		
}


/*----------------------------------------------------------------------------*/
/*								HELPERS									      */
/*----------------------------------------------------------------------------*/
/* 
O(n)
merges adjacent free chunks. 
*/
static void MergeAdjacentFree(vsa_t *block)
{
	vsa_t *block_iter = block;
	
	assert(block);

	while(block_iter->size < 0 && NEXT_BLOCK(block_iter)->size < 0)
	{
		block->size = block_iter->size - (long)META_SIZE + block_iter->size;
		block_iter = NEXT_BLOCK(block_iter);
	}
	
	return;
}


