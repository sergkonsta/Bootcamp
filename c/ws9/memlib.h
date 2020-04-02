/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    SENT						**
*****************************************/

#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/
#include <assert.h>		/*for assert*/
#include <string.h>		/*for original memset*/

/*MACROS for the tests*/
#define SIZE_OF_NULL_TERM (1)
#define CHAR_TO_MEMSET ('$')
#define NUMBER_OF_PLACES (20)
#define SIZE_OF_MEM (20)

#define INT_FOR_ITOA (123456789)
#define BASE_FOR_ITOA (10)

/*Test Function declarations*/
int TestMemSet(char *s1, char *s2);
int TestMemCpy(char *s1, char *s2);
int TestMemMove(char *src, char *dest);
int TestIntToString(int i, unsigned int base);

/*Memlib functions declarations*/
void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);

char *IntToString(int num, char *str, unsigned int base);


/*Helper funcs*/
int ZeroMem(char *s);

