/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    ???						**
*****************************************/

#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/
#include <assert.h>		/*for assert*/
#include <string.h>		/*for original memset*/

/*MACROS for the tests*/
#define CHAR_TO_MEMSET ('$')
#define NUMBER_OF_PLACES (20)
#define SIZE_OF_MEM (20)

/*Test Function declarations*/
int TestMemSet(char *s1, char *s2);
int TestMemCpy(char *s1, char *s2);

/*Memlib functions declarations*/
void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);

/*Helper funcs*/
int ZeroMem(char *s);

