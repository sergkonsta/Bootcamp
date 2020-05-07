
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      07.05.2020               **
**  Reviewer:  Roy						**
**  Status:    Sent						**
*****************************************/	



struct fsa
{
	size_t next_free; 	/* offset of next available block */
	size_t block_size;	/* size of each block*/
	size_t num_blocks; 	/* total number of blocks in pool*/
} fsa_t;

/*----------------------------------------------------------------------------*/
/* 
O(1) 
return minimal size in bytes for all block allocations:

size needed:
			- sizeof(fsa_t)
			- (sizeof(size_t) + block_size ) * blocks_number
*/
size_t SuggestSize(size_t block_number, size_t block_size)
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
*/
fsa_t *Init(void *mem_segment, size_t size, size_t block_size);


/*----------------------------------------------------------------------------*/
/*
O(1) 
allocate 1 block_size 
*/
void *Alloc(fsa_t *pool);
/*----------------------------------------------------------------------------*/
/*
O(1) free block
*/
void Free(void *block);
/*----------------------------------------------------------------------------*/
/*
O(n) 
Return number of free blocks in mem_pool 
*/
size_t CountFree(fsa_t *pool);
