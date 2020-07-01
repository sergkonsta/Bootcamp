/*
Developer: Sergey Konstantinovsky
Date:      30.06.2020
Reviewer:  Eden
*/

#include <stdio.h>		/*printf, size_t*/
#include <sys/timeb.h>	/*ftime*/

#define FTIME ((end_time_ms.time * 1000 + end_time_ms.millitm) -\
				(start_time_ms.time * 1000 + start_time_ms.millitm))

#define NUM (123456)

int array[1] = {0};

static void SumOfDivisorsImp()
{
	size_t sum_of_divisors = 0;
	size_t i = 0;
	
	for (i = 1; i < NUM; ++i)
	{
		if (0 == NUM % i)
		{
			sum_of_divisors += i;
		}
	}

	array[0] = (int)sum_of_divisors;

	return;
}


int main()
{
	struct timeb start_time_ms = {0};
	struct timeb end_time_ms = {0};
	
	ftime(&start_time_ms);
	
	SumOfDivisorsImp();	

	ftime(&end_time_ms);
	
	printf("\nSuccess.\nTime elapsed from start: %ld[mSec].\n",FTIME);
	printf("sum divisors %d\n", array[0]);
	printf("num of threads 1.\n");

	return 0;
}






