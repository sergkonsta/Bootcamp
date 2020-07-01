/*
Developer: Sergey Konstantinovsky
Date:      30.06.2020
Reviewer:  Eden
*/

#include <stdio.h>		/*printd*/
#include <unistd.h>		/*sleep*/
#include <pthread.h>	/*pthread_create*/
#include <sys/timeb.h>	/*ftime*/

#define FTIME ((end_time_ms.time * 1000 + end_time_ms.millitm) -\
				(start_time_ms.time * 1000 + start_time_ms.millitm))

#define NUM_OF_THREADS (4)
#define NUM (123456)

static void *ThreadHandlerEx4Imp(void *arg);

int main()
{
	size_t i = 0;
	size_t sum_of_divisors = 0;
	
	void *sum = NULL;
	
	pthread_t thread[NUM_OF_THREADS] = {0};
	
	struct timeb start_time_ms = {0};
	struct timeb end_time_ms = {0};
	
	ftime(&start_time_ms);
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_create(&thread[i], NULL, ThreadHandlerEx4Imp, (void *)i);
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(thread[i], &sum);
		sum_of_divisors += (size_t)sum;

	}
	
	ftime(&end_time_ms);
	
	printf("\nSuccess.\nTime elapsed from start: %ld[mSec].\n",FTIME);
	printf("sum divisors %ld\n", sum_of_divisors);
	printf("num of threads %d\n", NUM_OF_THREADS);

	return 0;
}


/*workload using sum of divisors for a RANGE of nums*/
static void *ThreadHandlerEx4Imp(void *arg)
{
	size_t sum_of_divisors = 0;
	size_t i = 1 + ((size_t)arg * (NUM / NUM_OF_THREADS));
	size_t end_of_range = i + (NUM / NUM_OF_THREADS);

	for (; i < end_of_range; ++i)
	{
		if (0 == NUM % i)
		{
			sum_of_divisors += i;
		}
	}

	return (void *)sum_of_divisors;
}

