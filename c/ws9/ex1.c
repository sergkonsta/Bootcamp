
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    ???						**
*****************************************/		

#include <stddef.h>		/*for size_t*/

void *Memset(void *s, int c, size_t n)
{
	void *temp_pointer = s;

	while(n > 0)
	{
		*(int *)&temp_pointer = c;
		*(int *)&temp_pointer += 1;
		--n;
	}
	
	return(s);
}

