/*
Developer: Sergey Konstantinovsky
Date:      30.06.2020
Reviewer:  Eden
*/

/*
EX1:	joined threads - w/o return value check.
time w/o -O3: 1922 ~ 2024 mSec
time w/  -O3: 1807 ~ 2210 mSec
*/

#include <stdio.h>		/*printd*/
#include <unistd.h>		/*sleep*/
#include <pthread.h>	/*pthread_create*/
#include <sys/timeb.h>	/*ftime*/

#define HUNDRED_K (100000)

#define FTIME ((end_time_ms.time * 1000 + end_time_ms.millitm) -\
				(start_time_ms.time * 1000 + start_time_ms.millitm))

size_t g_s[HUNDRED_K] = {0};

static void *ThreadHandlerEx1Imp(void *arg);


int main()
{
	size_t i = 0;

	struct timeb start_time_ms;
	struct timeb end_time_ms;	
	
	pthread_t threads_arr[HUNDRED_K];
	
	ftime(&start_time_ms);
	
	for (i = 0; i < HUNDRED_K; ++i)
	{
		/*creates threads*/
		pthread_create(&(threads_arr[i]), NULL, ThreadHandlerEx1Imp, (void *)i);
	}
	
	ftime(&end_time_ms);
	
	sleep(10);
	
	for (i = 0; i < HUNDRED_K; ++i)
	{
		if (i != g_s[i])
		{
			printf("\nfirst index of unfilled array: %lu\n",i);
			return 1;
		}
	}
	
	printf("\nSuccess.\nTime elapsed from start: %ld[mSec].\n",FTIME);
	
	return 0;
}


static void *ThreadHandlerEx1Imp(void *arg)
{	
	g_s[(size_t)arg] = (size_t)arg;
	
	return arg;
}
