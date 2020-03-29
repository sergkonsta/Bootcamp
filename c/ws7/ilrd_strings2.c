
#include <assert.h>        /*  for assert() */
#include <ctype.h>         /*  for tolower() inside StrCmpCmp  */
#include <stdlib.h>        /*  for abs() ; malloc()            */
#include <string.h>        /*  for strlen(), strdup() used in StrDup     */

#include "ilrd_strings.h"


/****************************************
**  Developer: Sergey Konstantinovsky  **
**  Date:      11.03.2020              **
**  Reviewer:  Yael Bar Avraham        **
**  Status:    Approved                **
****************************************/



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

/* comparing 2 strings disregarding lower-case and upper-case
 differences using tolower() */

int StrCaseCmp(const char *s1, const char *s2)
{
	while((tolower(*s1) == tolower(*s2)) && (*s1 != '\0'))
	{
		s1++;
		s2++;
	}
	
	return (*s1 - *s2);

}

