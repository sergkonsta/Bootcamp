
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    ???						**
*****************************************/		

#include <stddef.h>		/*for size_t*/

void *Memset(void *s, int c, size_t n)
{
	char *temp_pointer = (char *)s;

	while(n > 0)
	{
		*temp_pointer = c;
		temp_pointer += 1;
		--n;
	}
	
	return(s);
}

