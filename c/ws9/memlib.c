
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    ???						**
*****************************************/		

#include <stdlib.h>		/*for atoi*/
#include <stddef.h>		/*for size_t*/
#include <assert.h>		/*for assert*/

/*Memsetting byte by byte with typecast to char - ignoring any offsets*/
void *MemSet(void *s, int c, size_t n)
{
	char *temp_pointer = (char *)s;
	
	assert(NULL != s);
	
	while(n > 0)
	{
		*temp_pointer = c;
		temp_pointer += 1;
		--n;
	}
	
	return(s);
}


/*Memcopying byte by byte with typecast to char - ignoring any offsets*/
void *MemCpy(void *dest, const void *src, size_t n)
{
 	char *temp_src = (char *)src;
	char *temp_dest = (char *)dest;
	
	assert(NULL != dest && NULL != src);
	
	while(0 < n)
	{
		*temp_dest = *temp_src;
		++temp_dest;
		++temp_src;
		--n;
	}

	return dest;	
}



/*Memmoving byte by byte with typecast to char - ignoring any offsets

	check overlap - (dest - src)-->convert to hex 
		if (dest - src)hex > n    --> no overlap
		if (dest - src)hex < n    --> yes overlap 
			-->yes overlap && (dest-src) < 0 --> overlap at end of dest 
						--> start move from the start of src to start of dest
			-->yes overlap && (dest-src) > 0 --> overlap at start of dest
						--> start move from end of src to end of dest 	
		*/
void *Memmove(void *dest, const void *src, size_t n)
{
	char *temp_src = (char *)src;
	char *temp_dest = (char *)dest;
	
	assert(NULL != dest && NULL != src);
	
	/*check overlap here - move should start from end of dest*/
	if(0xNUMBER_OF_PLACES > (temp_dest - temp_src) && 0 < (temp_dest - temp_src))
	{
	
	}
	
	while(0 < n)
	{
		*temp_dest = *temp_src;
		++temp_dest;
		++temp_src;
		--n;
	}

	return dest;	
}








