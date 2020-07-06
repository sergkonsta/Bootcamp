/*
EX1 - single reader, single writer, no mutex

Developer: Sergey Konstantinovsky
Date:      01.07.2020
Reviewer:  Hanna
*/

#include <pthread.h>	/*threads*/
#include <unistd.h>		/*sleep*/
#include <stdio.h>		/*printf*/
#include <signal.h>		/*for sig_atomic_t*/

static void *ThreadProduceHandlerV1(void *arg);
static void *ThreadConsumeHandlerV1(void *arg);
static void Produce();
static void Consume();

sig_atomic_t g_busy = 0;

sig_atomic_t g_count = 0;		/*counter for data*/
int g_arr[50] = {0};			/*global array for data*/

int main ()
{
	pthread_t prod = 0;
	pthread_t cons = 0;
	
	pthread_create(&prod, NULL, ThreadProduceHandlerV1, NULL);
	pthread_create(&cons, NULL, ThreadConsumeHandlerV1, NULL);
	
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	
	return 0;
}


static void *ThreadProduceHandlerV1(void *arg)
{
	while (1)
	{
		while (1 == g_busy)
		{}
		
		sleep(1);
		
		g_busy = 1; 
		++g_count;
		Produce();
		g_busy = 0;	
	}
	
	return arg;
}


static void *ThreadConsumeHandlerV1(void *arg)
{
	while (1)
	{
		while (1 == g_busy)
		{}
		
		g_busy = 1; 
		Consume();
		g_busy = 0;	
	}
	
	return arg;
}

static void Produce()
{
	size_t i = 0;
	
	for (; i < 50; ++i)
	{
		g_arr[i] = g_count;
	}
}

static void Consume()
{
	size_t i = 0;
	
	for (; i < 50; ++i)
	{
		printf("%d ",g_arr[i]);
	}
	
	printf("\n\n");
}
