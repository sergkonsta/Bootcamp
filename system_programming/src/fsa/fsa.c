
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      07.05.2020               **
**  Reviewer:  Roy						**
**  Status:    Sent						**
*****************************************/	
#include <assert.h>		/*for assert*/

#include "fsa.h"

struct fsa
{
	size_t next_free; 	/* offset of next available block's data */
	size_t block_size;	/* size of each block*/
	size_t num_blocks; 	/* total number of blocks in pool*/
};

typedef struct block block_t;
struct block
{
	size_t offset;/*offset from head when block is allocated & from next_free data when free */
	size_t data; 		/*data*/
};

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
	
	return ( sizeof(fsa_t) + ((sizeof(size_t) * block_size) * block_number) );
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
	fsa_t *head = (fsa_t *)mem_segment;
	
	size_t block_amount = size / block_size;
	void *iter = mem_segment;
	block_t *blk = NULL;
	
	/*next_free points to next block's data*/
	head->next_free = sizeof(fsa_t) + sizeof(blk->offset);
	head->block_size = block_size;
	head->num_blocks = size / block_size;
		
	/*move iter to first meta-data*/
	iter =  (void *)( (size_t)iter + sizeof(fsa_t) );
	
	while(0 < block_amount)
	{
		/*typecast iter to represent the block*/
		blk = (block_t *)iter;
		
		/*place offset from next block's data*/	
		blk->offset = (2 * sizeof(blk->offset) + block_size);
		
		/*update free block amount*/	
		--block_amount;	
		
		/*move iter to next block's meta-data*/
		iter = 
		(void *)( (size_t)iter + sizeof(blk->offset) + block_size);		
	}	

	/*change lasts blocks offset to 0*/
	blk->offset = 0;
	
	return (head);
}


/*----------------------------------------------------------------------------*/
/*
O(1) 
allocate 1 block_size 
return: pointer to allocated block
*/
void *FSAAlloc(fsa_t *pool)
{
	/*typecast first free block from head*/
	block_t *blk = (block_t *)(	(size_t)pool + 
								pool->next_free - 
								sizeof(blk->offset));
		
	/*point head to next free & if last free put in pool 0*/
	if(0 == blk->offset)
	{
		pool->next_free = 0;
	}
	
	else
	{
		pool->next_free = blk->offset + ((size_t)blk - (size_t)pool);
	}
	
	/*put offset from allocated block to head - into blocks meta-data*/
	blk->offset = (size_t)blk - (size_t)pool;
		
	return (&blk->data);
}
/*----------------------------------------------------------------------------*/
/*
O(1) 
free block
recieving from user poiter to blocks data
*/
void FSAFree(void *block)
{
	/*typecast block*/
	block_t *blk = (block_t *)((size_t)block - sizeof(blk->offset));
	
	/*typecast head*/
	fsa_t *pool = (fsa_t *)((size_t)block - blk->offset);
		
	/*in block put offset from next free (adjusting the offset)*/	
	blk->offset = pool->next_free - ((size_t)block - (size_t)pool);
	
	/*pool->next_free recieves offset from freshly freed blocks data*/
	pool->next_free = (size_t)blk->data - (size_t)pool;

	return;
}




/*----------------------------------------------------------------------------*/
/*
O(n) 
Return number of free blocks in mem_pool 
*/
size_t FSACountFree(fsa_t *pool)
{
	size_t free_blocks = 0;
	
	/*typecast the first free block*/
	block_t *blk = 
	(block_t *)((size_t)pool + pool->next_free - sizeof(blk->offset));
	
	while(0 != blk->offset && 		/*until you reach last free block*/
		  0 != pool->next_free)		/*if all blocks are full*/
	{
		/*typecast each block passed for 'while loop' tests*/
		blk = (block_t *)((size_t)blk + blk->offset - sizeof(blk->offset));
		
		++free_blocks;
	}
	
	return (free_blocks);	
}








