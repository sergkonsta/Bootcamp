/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    SENT						**
*****************************************/
#include <stddef.h>		/*for size_t*/
#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/
#include <assert.h>		/*for assert*/
#include <string.h>		/*for original memset*/

#define UNUSED(x) (void)(x)

/*MACROS for the tests*/
#define SIZE_OF_NULL_TERM (1)
#define CHAR_TO_MEMSET ('$')
#define NUMBER_OF_PLACES (20)
#define SIZE_OF_MEM (20)

/*Test Function declarations*/
int TestMemSet(char *s1, char *s2);
int TestMemCpy(char *s1, char *s2);
int TestMemMove(char *src, char *dest);

/*Memlib functions declarations*/
void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);

/*Helper funcs*/
int ZeroMem(char *s);
	
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				 
