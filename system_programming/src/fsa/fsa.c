
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      07.05.2020               **
**  Reviewer:  Roy						**
**  Status:    Sent						**
*****************************************/	
#include <assert.h>		/*for assert*/

#include "fsa.h"

#define WORD 8		/* length of machine word */

struct fsa
{
	size_t next_free; 	/* offset of next available block from fsa */
	size_t block_size;	/* size of each block*/
	size_t num_blocks; 	/* total number of blocks in pool*/
};

typedef struct block
{
	size_t offset;	/*offset from pool when block is allocated & from next_free when free */
	#ifdef DEBUG 
	fsa_t *pool;	/* points to memory pool that blk belongs */
	#endif	/* DEBUG */
}block_t;	

static void Swap(size_t *data_1, size_t *data_2);

/*----------------------------------------------------------------------------*/
/* 
O(1) 
return minimal size in bytes for all block allocations:

size needed:
			- sizeof(fsa_t)
			- (sizeof(size_t) + block_size ) * blocks_number
*/
size_t FSASuggestSize(size_t block_number, size_t block_size)
{
	assert (block_number > 0);	
	assert (block_size > 0);
	
	return ( sizeof(fsa_t) + 
			 block_number * ((block_size - 1)/WORD + 1) * WORD + 
		  	 block_number * (sizeof(block_t)));	
}


/*----------------------------------------------------------------------------*/
/* 
O(1) 
Initiate fixed size memory pool 
ptr points to first address in block
size - size of segment
block_size
return pool struct 

					 ____________________________<-- fsa_t 
					|______next_free_______|
					|______block_size______|	 
					|______num_blocks______|_____
					|_____meta_data_1______|_____<-- offset 
					|					   |
					|					   |
					|		block 1		   |
					|					   |
					|______________________|_____
					|_____meta_data_2______|_____<-- offset 
					|					   |
					|					   |
					|		block 2		   |
					|					   |
					|______________________|_____
					|_____meta_data_2______|_____<-- offset 
					|					   |
					|		block 3		   |
								.
								.
								.
								
*/
fsa_t *FSAInit(void *mem_segment, size_t size, size_t block_size)
{	
	/*define pool struct at begining of mem_segment*/
	fsa_t *pool = (fsa_t *)mem_segment;
	
	block_t *blk = NULL;
	size_t offset_iter = 0;
	
	assert(NULL != mem_segment);
			
	/*next_free points to next block while alligned*/
	pool->next_free = sizeof(fsa_t);
	pool->block_size = sizeof(block_t) + (((block_size - 1)/WORD + 1) * WORD);
	pool->num_blocks = (size - sizeof(fsa_t))/ pool->block_size;		
		
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
}


/*----------------------------------------------------------------------------*/
/*
O(1) 
allocate 1 block_size 
return: pointer to allocated block or NULL if all no memory left
*/
void *FSAAlloc(fsa_t *pool)
{
	block_t *blk = NULL;
	
	assert(NULL != pool);
		
	/* if all blocks are full */
	if (0 == pool->next_free)
	{
		return (NULL);
	}	
	
	/* points to next free block */
	blk = (void *)((char *)pool + pool->next_free);

	/* switch offset of fsa control unit with allocated blocks offset */
	Swap(&(pool->next_free), &(blk->offset));

	return ((char *)blk + sizeof(block_t));
}


/*----------------------------------------------------------------------------*/
/*
O(1) 
free block
recieving from user poiter to blocks data
*/
void FSAFree(void *block)
{
	block_t *blk = NULL;
	fsa_t *pool = NULL;

	assert(NULL != block);

	/* get address of block to free */
	blk = (block_t *)((char *)block - sizeof(block_t));

	/* get address of pool */
	pool = (fsa_t *)((char *)blk - blk->offset);

	/* check if block was created in this pool */
	#ifdef DEBUG
	if (blk->pool != pool)
	{
		return;
	}
	#endif

	/* update offsets */
	Swap(&blk->offset, &pool->next_free);

	return;
}


/*----------------------------------------------------------------------------*/
/*
O(n) 
Return number of free blocks in mem_pool 
*/
size_t FSACountFree(fsa_t *pool)
{
	block_t *blk = NULL;
	size_t loop_iter = 0;
	size_t free_blocks = 0;

	assert(NULL != pool);

	/* initialize variables for a loop */
	loop_iter = pool->next_free;
	blk = (block_t *)((char *)pool + pool->next_free);

	/* run all block (check if their offset != 0) */
	while (0 != loop_iter)
	{
		/* check if block is empty (doesn't point to itself:
		(current pointer-offset doesn't equal to pool) */
		if ((char *)pool != ((char *)blk - blk->offset))
		{
			++free_blocks;
		}

		blk = (block_t *)((char *)pool + loop_iter);

		loop_iter = blk->offset;
	}
	
	return (free_blocks);	
}

/*----------------------------------------------------------------------------*/
/*								HELPERS										  */
/*----------------------------------------------------------------------------*/

/*swapper*/
static void Swap(size_t *data_1, size_t *data_2)
{
	size_t temp = *data_1;
	*data_1 = *data_2;
	*data_2 = temp;

	return;	
}




