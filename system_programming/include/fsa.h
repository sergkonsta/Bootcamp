#ifndef __OL87_FSA_H__
#define __OL87_FSA_H__

#include <stddef.h>	/* for size_t */

typedef struct fsa fsa_t;

/* 
O(1) 
return minimal size in bytes for all block allocations 
*/
size_t FSASuggestSize(size_t block_number, size_t block_size);

/* 
O(1) 
Initiate fixed size memory pool 
ptr points to first address in block
size - size of segment
block_size
return pool struct 
*/
fsa_t *FSAInit(void *mem_segment, size_t size, size_t block_size);

/*
O(1) 
allocate 1 block_size 
return: pointer to allocated block or NULL if all no memory left
*/
void *FSAAlloc(fsa_t *pool);

/*
O(1) free block
*/
void FSAFree(void *block);

/*
O(n) 
Return number of free blocks in mem_pool 
*/
size_t FSACountFree(fsa_t *pool);

#endif /* Closing OL87 FIXED SIZE ALLOCATION header file */
