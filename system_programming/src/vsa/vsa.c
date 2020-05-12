
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      10.05.2020               **
**  Reviewer:  Eliran					**
**  Status:    Approved					**
*****************************************/	

#include <stddef.h>		/*for size_t*/
#include <assert.h>		/*for assert*/

#include "vsa.h"

#define ABS(x) ((x < 0) ? ((-1) * x) : x)

#define WORD_SIZE (sizeof(size_t))
#define META_SIZE (sizeof(vsa_t))

#define FREE (-1)

#define NEXT_BLOCK(x) ((vsa_t *)((char *)x + META_SIZE + (size_t)ABS(x->size)))



struct vsa
{
	long size;		 
	#ifndef NDEBUG
	long tag; /*verification that chunk is from this pool*/
	#endif
};

static void MergeAdjacentFree(vsa_t *header);

/*					
	each size holds the size of its block (positive for allocated, 
											 negative for free) 
											 					
	vsa_t *------->	 ______________________
					|_____size__1__________|_____<-- size
					|					   |
					|					   |
					|		block 1		   |
					|					   |
					|______________________|_____
					|_____size__2__________|_____<-- size
					|					   |
					|					   |
					|		block 2		   |
					|					   |
					|______________________|_____
					|_____size__3__________|_____<-- size
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
Function: 	initializes memory pool
Return: 	pointer to initialized memory pool / NULL if not enough memory
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
Function: 	allocates memory
			combines additional free blocks
Return: 	pointer to allocated memory / NULL if no memory space was found
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
		if((long)(size_to_alloc + META_SIZE) < ABS(block->size))	
		{
			/* holds original size of free chunk - negative value*/
			free_block_size = block->size;
			
			/*hold return value - pointer to allocated space*/
			ret = (void *)((char *)block + META_SIZE);

			/*initialize meta-data*/
			block->size = (long)size_to_alloc;
			#ifndef NDEBUG
			block->tag = 0xDEADBEEF;
			#endif
			
			/*update block after allocation*/
			block = NEXT_BLOCK(block);		
			block->size = 
			free_block_size + (long)size_to_alloc + (long)META_SIZE;			
			break;
		}
		
		/*case of last block available, no room left for another meta-data*/
		else if ((long)(size_to_alloc) <= ABS(block->size) &&
				 (long)(size_to_alloc + META_SIZE) >= ABS(block->size) )
		{
			block->size *= FREE;
			ret =  ( (void *)((char *)block + META_SIZE) );
			break;
		}
		
		/*advance to next chunk, current can't be allocated (small/occupied)*/
		block = NEXT_BLOCK(block);	
	}

	/*if chunk with suitable size wasn't found*/
	return (ret);
}


/*----------------------------------------------------------------------------*/
/*
O(1) 
Function: 	frees block
Return: 	---
*/
void VSAFree(void *chunk)
{
	vsa_t *block = NULL;

	assert(chunk);

	/* get pointer to header */
	block = (vsa_t *)((char *)chunk - META_SIZE);

	assert(block->tag == 0xDEADBEEF);
	assert(block->size > 0);

	/* change header status to free */
	block->size = FREE * block->size;
	
	return;
}


/*----------------------------------------------------------------------------*/
/*
O(n) 
Function: 	finds largest free chunk of memory
		  	merges adjacent free blocks

Return: 	size_t of largest block found
			0 if none were found
*/

size_t VSALargestChunkAvailable(vsa_t *pool)
{
	long result = 0;
	vsa_t *block = pool;
	
	assert (NULL != pool);	
	
	/*while end of pool isn't reached*/
	while(0 != block->size)
	{
		/*check for adjacent free blocks and merge*/
		MergeAdjacentFree(block);			
		
		/*update if space is free and larger*/
		if(result > block->size)
		{
			result = block->size;
		}
		
		/* advance to next block */
		block = NEXT_BLOCK(block);	
	}
	
	return ( ABS(result) );		
}


/*----------------------------------------------------------------------------*/
/*								HELPERS									      */
/*----------------------------------------------------------------------------*/
/* 
O(n)
Function: merges adjacent free chunks.
Return: ---
*/
static void MergeAdjacentFree(vsa_t *block)
{
	vsa_t *block_iter = block;
	
	assert(block);

	while(block->size < 0 && NEXT_BLOCK(block_iter)->size < 0)
	{
		block->size += NEXT_BLOCK(block_iter)->size + (FREE * (long)META_SIZE);
	}
	
	return;
}


