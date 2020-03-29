
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


