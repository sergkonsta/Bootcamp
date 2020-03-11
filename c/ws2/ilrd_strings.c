
#include <stdlib.h> /*for abs()*/
#include "ilrd_strings.h"


/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      11.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Approved                **
****************************************/


/*checking strings length and returningthe length in size_t*/

size_t StrLen(const char *s)
{
	size_t counter = 0;
	
	for(; *s != '\0'; counter++, s++) {}

	return counter;
}



/* comparing 2 strings and returning 0 for equality of the result of ascii char substraction: s1-s2 */

int StrCmp(const char *s1, const char *s2)
{
	while((*s1 == *s2) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	
	return (*s1 - *s2);
}



/* copying 1 string into the destination */

char *StrCpy(char *dest, const char *src)
{
	char *start = dest;		 /*save start pointer for the return*/

	while(*src != '\0')
	{
		*dest = *src;		
		src++;
		dest++;
	}

	*dest = '\0';
	
	return start;
}

/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      11.03.2020              **
**  Reviewer:  Elimelech               **
**  Status:    Approved                **
****************************************/

/* comparing 2 strings disregarding lower-case and upper-case differences using ascii */

int StrCaseCmp(const char *s1, const char *s2)
{

	/*1st condition -  char equality AND not end of str
	  2nd condition - s2 char is lowercase AND s1 char is uppercase AND they are the same letter
	  3rd condition - s1 char is lowercase AND s2 char is uppercase AND they are the same letter */

	while(((*s1 == *s2)&&(*s1 != '\0'))||
	((65 <= *s1)&&(90 >= *s1)&&(97 <= *s2)&&(122 >= *s2)&&(32 == abs(*s1 - *s2)))||
	((65 <= *s2)&&(90 >= *s2)&&(97 <= *s1)&&(122 >= *s1)&&(32 == abs(*s1 - *s2))))
	{
		s1++;
		s2++;
	}
	
	return (*s1 - *s2);
}





































