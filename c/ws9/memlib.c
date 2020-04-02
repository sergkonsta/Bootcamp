
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    SENT						**
*****************************************/		

#include "memlib.h"

/*Memsetting word by word when possible*/
void *MemSet(void *s, int c, size_t n)
{	
	char *char_p = (char *)s;
	
	size_t *word_p = NULL; 
	size_t words_left = 0;
	size_t word_c = (size_t)c; 
	
	assert(NULL != s);

	/*enlarge c to 'word size c' */
	word_c |= word_c << sizeof(size_t); 
	word_c |= word_c << sizeof(size_t) * 2;
	word_c |= word_c << sizeof(size_t) * 4;
	
	/*set char by char while char_p is not aligned in memmory and n is not 0*/
	while ((0 != ((size_t)char_p % sizeof(size_t)) && 0 != n))
	{
       	*char_p = (char)c;		
		++char_p;
		--n;	
	}

	/*typecast for word counting*/
	word_p = (size_t *)char_p;

	/*save word amount counter*/
	words_left = n / sizeof(size_t);

	/*save remainder of n*/
	n %= sizeof(size_t);

	/* puts blocks of 8 bytes inside s */
	while (0 != words_left)
	{
        *word_p = word_c;
		++word_p;
		--words_left;
	}
	
	/*typecast back to char counting*/
	char_p=(char *)word_p;

	/*sets the remaining chars*/
	while (0 != n)
	{
		*char_p = (char)c;
		++char_p;
		--n;
	}

	return s;	
}


/*Memcopying word by word when possible with typecast to char - 
	ignoring any offsets between the two mem blocks*/
void *MemCpy(void *dest, const void *src, size_t n)
{
 	char *char_psrc = (char *)src;
	char *char_pdest = (char *)dest;
	
	size_t *word_psrc = NULL;
	size_t *word_pdest = NULL;
	
	size_t words_left = 0;
	
	assert(NULL != dest && NULL != src);
				
	/*set char by char while char_psrc & char_pdest is not aligned in memory
	 and n is not 0*/
	while ((0 != ((size_t)char_psrc % sizeof(size_t))) 
			&& (0 != n)
			&& (0 != ((size_t)char_pdest % sizeof(size_t))))
	{
       	*char_pdest = *char_psrc;		
		++char_pdest;
		++char_psrc;
		--n;	
	}

	/*typecast for word counting*/
	word_psrc = (size_t *)char_psrc;
	word_pdest = (size_t *)char_pdest;

	/*save word amount counter*/
	words_left = n / sizeof(size_t);

	/*save remainder of n*/
	n %= sizeof(size_t);

	/* copies blocks of 8 bytes from src to dest */
	while (0 != words_left)
	{           
        *word_pdest = *word_psrc;
		++word_pdest;
		++word_psrc;
		--words_left;
	}
	
	/*typecast back to char counting*/
	char_pdest=(char *)word_pdest;
	char_psrc=(char *)word_psrc;
	
	/*copies the remaining chars*/
	while (0 != n)
	{
		*char_pdest = *char_psrc;
		++char_pdest;
		++char_psrc;
		--n;
	}	

	return dest;	
}



/*Memmoving byte by byte with typecast to char - ignoring any offsets

	check overlap - (dest - src)-->convert to hex 
		if (dest - src)hex > n    --> no overlap
		if (dest - src)hex < n    --> yes overlap 
		
			-->yes overlap && (dest-src) < 0 --> overlap at end of dest 
				no change--> start move from the start of src to start of dest
				
			-->yes overlap && (dest-src) > 0 --> overlap at start of dest
  						 --> start move from end of src to end of dest 	
		*/
void *MemMove(void *dest, const void *src, size_t n)
{
	char *temp_src = (char *)src;
	char *temp_dest = (char *)dest;
	
	/* 1 = not overlaps
	  -1 = overlaps 		*/
	int overlap_status = 1;
	size_t counter = 0;
	
	assert(NULL != dest && NULL != src);
	
	/*check if end of source overlaps with start of dest
	  then move should start from end of dest*/
    for (counter = 0; counter < n; ++counter)
    {
    	if (temp_src + counter == temp_dest)
    	{
    		overlap_status = -1;    		
    	}
    }
	
	/*if overlap -> update start of move pointers*/
	if(-1 == overlap_status)
	{
		temp_src += counter;
		temp_dest += counter;
	}
	
	/*performs move from begining or from end - according to overlap status*/
	while(0 < n)
	{
		*temp_dest = *temp_src;
		temp_dest += overlap_status;
		temp_src += overlap_status;
		--n;
	}

	return dest;	
}


/*--------------------------------------------------------------------------*/
/* Int to string algorithm:

-recieve an int, pointer to str, base
-check amount of digits and allocate enough memory 
 for the str and the null terminator
-take each digit of the int and convert it to char
-place each converted char to the str
-end with null terminator
*/
char *IntToString(int i, char *str, unsigned int base)
{
	int tmp = i;
	
	/*change to int*/
	size_t digits = 0;

	assert(NULL != str);
	
	while(0 != tmp)
	{
		tmp /= 10;
		++digits;
	}
	
	/*null terminator at end of str*/
	*(str + digits) = '\0';
	--digits;
	
	while(0 != i)
	{
		/*48 is ascii diff from int for numbers*/
		*(str + digits) =  (i % base) + 48;
		i /= base;
		
		/*might drop on last loop*/
		--digits;
	}
	
	return str;	
}





/*--------------------------------------------------------------------------*/
/* string to int algorithm:

-recieve a str and a base
-check its length
-for every char in the string from head to end (according to atoi()):
 check if the char fits the base
	-if yes: add to int in selected base
	-if not: return int
	
	why up to base 36? --> 0-9 + A-Z - total of 36 chars.. 
	won't be what to represent the chars of the higher bases with.
*/
/*--------NOT DONE, NEED LUT TABLE for 0-9 a-z-------------*/
int StringToInt(const char *str, unsigned int base)
{
	int result = 0;
	size_t c = 0;
	int base_counter = 0;
	
	/*got to end of str*/
	while('\0' != *(str))
	{
		++str;
		++c;
	}
	--str; 
		
	while(0 != c)
	{		
		result += Power(base,base_counter) * (int)(*str - 0x30);
		++base_counter;
		--str;	
		--c; 
	}
	
	return result;	
}

int Power(int x, int y)
{	 
    int temp = 0; 
    
    if( y == 0) 
    {
    	return 1; 
    }
    
    temp = Power(x, y/2); 
    
    if (y%2 == 0) 
    {
    	return temp*temp; 
    }
    
    else
    {
    	return x*temp*temp; 
    }
}



























