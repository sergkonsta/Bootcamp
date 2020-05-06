
/*free list*/

typedef struct fsa 
{
	size_t next_free; /* offset of next available block */
	size_t block_size;
	size_t num_blocks; /*total number of blocks in pool*/
} fsa_t;

/* O(1) return minimal size in bytes for all block allocations */
size_t SuggestSize(size_t block_number, size_t block_size);

/* O(1) Initiate fixed size memory pool 
	ptr points to first address in block
	size - size of segment
	block_size
	return pool struct */
fsa_t *Init(void *mem_segment, size_t size, size_t block_size);

/*O(1) allocate 1 block_size */
void *Alloc(fsa_t *pool);

/*O(1) free block*/
void Free(void *block);

/*O(n) Return number of free blocks in mem_pool */
size_t CountFree(fsa_t *pool);

offset - if not allocated - holder points to next_free
		if allocated - holder points to struct 
		when free - write ->next_free offset in my holder. put own offset in ->next_free
		when alloc - write pool_struct offset in holder


