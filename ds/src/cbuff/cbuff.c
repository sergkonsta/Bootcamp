
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      21.04.2020               **
**  Reviewer:  Yael						**
**  Status:    SENT						**
*****************************************/

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/

#include "cbuff.h"

struct circular_buffer
{
	char *read_p; 		/*read pointer*/
	char *write_p;		/*write pointer*/
	size_t capacity;	/*size of 'flex' array*/
	char buffer[1];		/*'flex' array*/
};

/*----------------------------------------------------------------------------*/
/*size allocated for 'flex array' is [capacity + 1]
	 (extra byte already exists in the struct definition)
	 extra byte to be used when making sure write_p doesn't pass 
	 read_p while writing */
	 
c_buff_t *CirBufferCreate(size_t capacity)
{	
	c_buff_t *cbuff = NULL;	
	
	size_t alloc_size = (sizeof(c_buff_t) +	(sizeof(cbuff->buffer) * capacity));

	assert(0 != capacity);
	
	cbuff = (c_buff_t *)malloc(alloc_size);
	
	/*placing indexes at first array cell*/
	cbuff->read_p = cbuff->buffer;
	cbuff->write_p = cbuff->buffer;
	cbuff->capacity = capacity;
	
	return (cbuff);
}


/*----------------------------------------------------------------------------*/

/*free allocation and write nulls in every used memory */
void CirBufferDestroy(c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	while(0 != cbuff->capacity)
	{
		cbuff->buffer[cbuff->capacity] = 0x0;
		--cbuff->capacity;
	}
	
	cbuff->read_p = NULL;
	cbuff->write_p = NULL;
	
	free(cbuff);
	
	cbuff = NULL;

	return;
}


/*----------------------------------------------------------------------------*/
/*returns amount of steps left from write_p to read_p*/

size_t CirBufferFreeSpace(const c_buff_t *cbuff)
{
	size_t steps = 0;	
	
	int address_diff = cbuff->write_p - cbuff->read_p;
	
	assert(NULL != cbuff);
	
	/*write_p is ahead of read_p in 'flex array' buffer*/
	if(0 <= address_diff)
	{
		steps = cbuff->capacity - address_diff;
	}
	
	/*read_p is ahead of write_p in 'flex array' buffer*/
	else
	{
		steps = address_diff;
	}
		
	return (steps);
}


/*----------------------------------------------------------------------------*/
/*shows how much is ledt to read*/
size_t CirBufferSize(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);

	return (cbuff->capacity - CirBufferFreeSpace(cbuff));
}


/*----------------------------------------------------------------------------*/
/*empty when read and write pointers point to the same place*/
int CirBufferIsEmpty(const c_buff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->read_p == cbuff->write_p);
}



/*----------------------------------------------------------------------------*/
/*before every write action make sure write_p is not located before read_p
if it is, stop writing and return number of bytes written*/

/*	if num_to_write is greater than memory segment pointed by src, 
	then unknown data will be copied*/

/*return on error for:
	
	- EFAULT src is outside of accessible adress space
	
	- EINVAL cbuff unreadable 	also src/num_to_write/cbuff offset not aligned,
								but we work in 1 bytes intervals so irrelevant
			
	- ENOSPC cbuff has no space to be written to*/

ssize_t CirBufferWrite(c_buff_t *cbuff, const void *src, size_t num_to_write)
{
	ssize_t written_counter = 0;
	char *tmp = (char *)src;
	
	if(NULL == src || NULL == cbuff)
	{
		written_counter = (-1);
	}
	
	while(	(-1) != written_counter &&
			0 != CirBufferFreeSpace(cbuff) &&
			(size_t)written_counter < num_to_write) 
	{		
		*cbuff->write_p = *tmp;		
		++cbuff->write_p;
		++tmp;
		++written_counter;
	}	
	
	if(	0 == CirBufferFreeSpace(cbuff) && 0 == written_counter)
	{
		written_counter = (-1);
	}
	
	return (written_counter);
}



/*----------------------------------------------------------------------------*/
/*make sure read_p doens't pass write_p*/

/*return on error for:
	
	- EFAULT dest is outside of accessible adress space
	
	- EINVAL cbuff unreadable 	also dest/num_to_read/cbuff offset not aligned,
								but we work in 1 bytes intervals so irrelevant*/
ssize_t CirBufferRead(c_buff_t *cbuff, void *dest, size_t num_to_read)
{
	ssize_t read_counter = 0;
	char *tmp = (char *)dest;
		
	if(NULL == dest || NULL == cbuff)
	{
		read_counter = (-1);
	}
			
	while(	(-1) != read_counter &&
			cbuff->read_p != cbuff->write_p &&
			(size_t)read_counter < num_to_read)							
	{		
		*tmp = *cbuff->read_p;		
		++cbuff->read_p;
		++tmp;
		++read_counter;
	}
	
	return (read_counter);
}



















