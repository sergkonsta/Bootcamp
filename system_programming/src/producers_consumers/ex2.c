/*
EX2 - multiple producers and consumers, queue + 1 mutex

Developer: Sergey Konstantinovsky
Date:      01.07.2020
Reviewer:  Hanna
*/

#include <pthread.h>	/*threads*/
#include <unistd.h>		/*sleep*/
#include <stdio.h>		/*printf*/

#include "queue.h"

#define NUM (20)
#define ARR_LENGTH (20)

static void *ThreadProduceHandler(void *arg);
static void *ThreadConsumeHandler(void *arg);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static queue_t *queue;
static int array[ARR_LENGTH];

int main()
{
    pthread_t producer[NUM];
    pthread_t consumer[NUM];
  
    int status = 0;
    int exit_status = -1;
    
    size_t i = 0;

    queue = QueueCreate();
    if (NULL == queue)
    {
        return 0;
    }

    for (i = 0; i < ARR_LENGTH; ++i)
    {
        array[i] = i;
    }

	/*create producers and consumers threads*/
    for (i = 0; i < NUM; ++i)
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

	/*join all producers*/
    for (i = 0; i < NUM; ++i)
    {
        pthread_join(producer[i], NULL);
    }

    pthread_mutex_lock(&lock);
    
    QueueEnq(queue, &exit_status);
    
    pthread_mutex_unlock(&lock);

	/*join all consumers*/
    for (i=0; i < NUM; ++i)
    {
        pthread_join(consumer[i], NULL);
    }

    puts("the end");
    QueueDestroy(queue);
    return 0;
}

void *ThreadProduceHandler(void *arg)
{
    int i = 0;

    for (i=0; i < ARR_LENGTH; ++i)
    {
        pthread_mutex_lock(&lock);
        QueueEnq(queue, &array[i]);
        pthread_mutex_unlock(&lock);

        sleep(1);
    }
	
	puts("produced");
  
    return arg;
}

void *ThreadConsumeHandler(void *arg)
{
    int *to_print = array;

	sleep(2);	
	
    while (-1 != array[0])
    {
        pthread_mutex_lock(&lock);
      
        if (QueueIsEmpty(queue))
        {
            pthread_mutex_unlock(&lock);
            continue;
        }

        to_print = QueuePeek(queue);
      
        QueueDeq(queue);
      
        printf("action = %d\n", *(int*)to_print);
       
        if (-1 == *to_print)
        {
           array[0] = *to_print;
        }
       
        pthread_mutex_unlock(&lock);

        sleep(1);
    }
	
	puts("consumed");

    return arg;
}

