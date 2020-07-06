/*
EX6 - barrier - single producer, multiple consumers,
	producer waits until all consumers read 1 time exactly 
	1 coditional variable, 1 mutex, 1 semaphore

Developer: Sergey Konstantinovsky
Date:      01.07.2020
Reviewer:  Hanna
*/
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>		/*sig_atomic_t*/
#include <stdio.h>		/*printf*/
#include <unistd.h>		/*sleep*/

#define TOTAL_CONSUMERS (50)

void FlagInit();
void ConsumersInit();
void *Consumer(void *thread_arg);
void *Producer(void *thread_arg);

int g_data[TOTAL_CONSUMERS] = {0};

pthread_t consumers[TOTAL_CONSUMERS] = {0};

size_t g_data_index = 0;

sem_t g_amount_read_sem;

volatile sig_atomic_t g_data_version;
pthread_cond_t data_version_cv;
pthread_mutex_t data_version_mutex;

int main()
{
	size_t i = 0;
	int status = 0;
	
	pthread_t producer = 0;
		
	sem_init(&g_amount_read_sem, 0, 0);
	
	FlagInit();
	
	ConsumersInit();
	
	status = pthread_create(&producer, NULL, &Producer, NULL);
	if (0 != status)
	{
		perror("error");
	}
	
	for (i = 0; i < TOTAL_CONSUMERS; ++i)
	{
		status = pthread_create(&consumers[i], NULL, &Consumer, NULL);
		if (0 != status)
		{
			perror("error");
		}
	}
	
	/*finish up*/
	pthread_join(producer, NULL);
	for (i = 0; i < TOTAL_CONSUMERS; ++i)
	{
		pthread_join(consumers[i], NULL);
	}
	
	sem_close(&g_amount_read_sem);
	
	puts("the end");

	return 0;

}


void FlagInit()
{
	/* Initialize the semaphore, mutex and condition variable. */
	pthread_mutex_init(&data_version_mutex, NULL);
	pthread_cond_init(&data_version_cv, NULL);
	
	/* Initialize the flag value. */
	g_data_version = 0;
}

void ConsumersInit()
{
	size_t i = 0;
	for(; i < 50; ++i)
	{
		consumers[i] = i;
	}
}

/*still need to remove race conditions of all consumers over the data*/
void *Consumer(void *thread_arg)
{
	size_t cons_idx = (size_t)thread_arg;
	int thread_data_version = 0;
	
	while (1) 
	{	
		/*Lock the mutex before accessing the flag value*/
		pthread_mutex_lock(&data_version_mutex);
		
		/*update data version*/
		thread_data_version = g_data_version;
		
		sem_post(&g_amount_read_sem);
		
		/*wait while data not ready*/
		while (thread_data_version == g_data_version)
		{
			pthread_cond_wait(&data_version_cv, &data_version_mutex);
		}
		
		/*data is ready now*/
		pthread_mutex_unlock(&data_version_mutex);
		
		/*consume*/
		printf("%d ", g_data[cons_idx]);
	}
	
	return NULL;
}

void *Producer(void *thread_arg)
{
	size_t i = 0;
	
	while (1) 
	{	
		/*wait while semaphore isn't 0*/
		for (i = 0; i < TOTAL_CONSUMERS; ++i)
		{
			sem_wait(&g_amount_read_sem);
		}
		
		/*replenish data*/
		++g_data_index;
		for (i = 0; i < 50; ++i)
		{
			g_data[i] = g_data_index;
		}
		
		/*lock mutex*/
		pthread_mutex_lock(&data_version_mutex);
		
		/*update data version*/
		++g_data_version;
		printf("\n\n");
		sleep(1);
		
		/*update all consumers that are currently waiting*/
		pthread_cond_broadcast(&data_version_cv);
		
		/*unlock mutex*/
		pthread_mutex_unlock(&data_version_mutex);
	}
	
	return thread_arg;
}

