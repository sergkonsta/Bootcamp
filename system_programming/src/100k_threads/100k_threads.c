/*
Developer: Sergey Konstantinovsky
Date:      30.06.2020
Reviewer:  Eden
*/

#include <pthread.h>	/*pthread_create*/


#define 100K (100000)

static int g_s[100K] = {0};

static void *thread_start_routine_ex1(void *arg);




int main()
{
	size_t i = 0;
	
	pthread_t *threads_arr[100K] = {NULL};
	
	for (i = 0; i < 100K; ++i)
	{
		pthread_create(threads_arr[i], NULL, thread_start_routine_ex1, (void *)&i);
	}
	
	return 0;
}





static void *thread_start_routine_ex1(void *arg)
{	
	g_s[*(size_t *)arg] = *(size_t *)arg;
}
