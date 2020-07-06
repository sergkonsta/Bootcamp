/*
EX4 - fixed size queue + 1 mutex + 2 semaphores

Developer: Sergey Konstantinovsky
Date:      01.07.2020
Reviewer:  Hanna
*/

#include <stdio.h>       /*printf*/
#include <pthread.h>     /*threads*/
#include <unistd.h>      /*sleep*/
#include <semaphore.h>   /*semaphore*/

#define NUM_OF_PLAYERS (25)
#define ARR_LENGTH (45)

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static sem_t available;
static sem_t empty;

static int array[ARR_LENGTH];
static int to_write = 0;
static int to_read = 0;

void *ThreadProduceHandler(void *arg);
void *ThreadConsumeHandler(void *arg);

int main()
{
	pthread_t producer[NUM_OF_PLAYERS];
	pthread_t consumer[NUM_OF_PLAYERS];

	int status = 0;
	size_t i = 0;

	sem_init(&available, 0, ARR_LENGTH);
	sem_init(&empty, 0, 0);

	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		status = pthread_create(&producer[i], NULL, &ThreadProduceHandler, NULL);
		if (0 != status)
		{
			perror("error");
		}

		status = pthread_create(&consumer[i], NULL, &ThreadConsumeHandler, NULL);
		if (0 != status)
		{
			perror("error");
		}
	}

	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		pthread_join(producer[i], NULL);
	}

	pthread_mutex_lock(&lock);

	to_read = ARR_LENGTH + 1;

	pthread_mutex_unlock(&lock);

	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		sem_post(&empty);
	}


	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		pthread_join(consumer[i], NULL);
	}

	puts("the end");

	return 0;
}

void *ThreadProduceHandler(void *arg)
{
	int i = 0;

	for (i = 0; i < ARR_LENGTH; ++i)
	{
		sem_wait(&available);
		
		pthread_mutex_lock(&lock);

		array[to_write] = i;
	
		++to_write;
		
		if (ARR_LENGTH == to_write)
		{
			to_write = 0;
		}

		pthread_mutex_unlock(&lock);

		sleep(1);
		
		sem_post(&empty);
	}
	
	puts("produced");
	
	return arg;
}

void *ThreadConsumeHandler(void *arg)
{
	while (1)
	{
		sem_wait(&empty);
		
		if (ARR_LENGTH < to_read)
		{
			break;
		}
		
		pthread_mutex_lock(&lock);

		printf("to_print = %d\n", array[to_read]);
		
		++to_read;
		
		if (ARR_LENGTH == to_read)
		{
			to_read = 0;
		}
		
		pthread_mutex_unlock(&lock);

		sleep(1);
		sem_post(&available);
	}

	puts("consumed");

	return arg;
}


