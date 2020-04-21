#ifndef __OL87_CIR_BUFFER__H__
#define __OL87_CIR_BUFFER__H__

#include <sys/types.h>	/*for ssize_t & size_t*/

typedef struct circular_buffer c_buff_t;

c_buff_t *CirBufferCreate(size_t capacity);

void CirBufferDestroy(c_buff_t *cbuff);

/*	returns amount of bytes written	*/
/*	if num_to_write is greater than memory segment pointed by src, 
	then unknown data will be copied*/
ssize_t CirBufferWrite(c_buff_t *cbuff, const void *src, size_t num_to_write);

/*returns amount of bytes read*/
ssize_t CirBufferRead(c_buff_t *cbuff, void *dest, size_t num_to_read);

/*returns 1 for empty buffer*/
int CirBufferIsEmpty(const c_buff_t *cbuff);

/*return amount of bytes free in buffer you can still write to*/
size_t CirBufferFreeSpace(const c_buff_t *cbuff);

/*returns amount of bytes left to read*/
size_t CirBufferSize(const c_buff_t *cbuff);

#endif /* __OL87_CIR_BUFFER__H__ */
