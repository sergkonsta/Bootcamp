/*
Developer: Sergey Konstantinovsky
Date:      30.06.2020
Reviewer:  Eden
*/

#include <stdio.h>		/*printf, size_t*/
#include <pthread.h>	/*pthread_create*/
#include <signal.h>		/*printf, size_t*/
#include <sys/timeb.h>	/*ftime*/
#include <omp.h> 		/*openMP*/

#define NUM_OF_THREADS (4)
#define NUM (1111111111)

#define FTIME ((end_time_ms.time * 1000 + end_time_ms.millitm) -\
				(start_time_ms.time * 1000 + start_time_ms.millitm))

int array[NUM_OF_THREADS] = {0};

static void *ThreadFunc(void *arg)
{
	size_t sum_of_divisors = 0;
	size_t i = 0;

	#pragma omp parallel
	{
		#pragma omp for
		for (i = 1 + ((size_t)arg * (NUM / NUM_OF_THREADS)); 
			i < 1 + ((size_t)arg * (NUM / NUM_OF_THREADS) + (NUM / NUM_OF_THREADS)); 
			++i)
		{
			if (0 == NUM % i)
			{
				sum_of_divisors += i;
			}
		}
		
	}

	array[(size_t)arg] = (int)sum_of_divisors;

	return NULL;
}


int main()
{
	size_t i = 0;
	size_t sum_of_divisors = 0;
	pthread_t thread[NUM_OF_THREADS] = {0};
	
	struct timeb start_time_ms = {0};
	struct timeb end_time_ms = {0};
	
	ftime(&start_time_ms);
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_create(&thread[i], NULL, ThreadFunc, (void *)i);
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(thread[i], NULL);
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		sum_of_divisors += array[i];
	}

	ftime(&end_time_ms);
	
	printf("\nSuccess.\nTime elapsed from start: %ld[mSec].\n",FTIME);
	printf("sum divisors %ld\n", sum_of_divisors);
	printf("num of threads %d\n", NUM_OF_THREADS);

	return 0;
}





