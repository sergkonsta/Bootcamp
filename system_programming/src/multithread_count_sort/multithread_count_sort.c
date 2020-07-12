/*
Project:	Multithreading count sort
Developer:	Sergey Konstantinovsky
Date:		12/07/2020
*/

#include <stdlib.h>		/*calloc*/
#include <stdio.h>		/*print, fopenqq*/
#include <assert.h>		/*assert*/
#include <ctype.h>		/*isalpha*/
#include <pthread.h>	/*pthread*/

#define DICT_PATH ("/usr/share/dict/american-english")
#define DICTIONARY_SIZE (102306)
#define LETTERS_IN_ABC (26)

#define NUM_OF_THREADS (1)
#define BIG_DATA (2)	

typedef struct thread_args
{
	char *sub_segment;
	size_t range;
	size_t sub_seg_size;
} thread_args_t;


char *CreateBigData(char *buffer, size_t *size_of_segment);
void DestroyBigData(char *buffer);
static size_t CountLetters(FILE *fp);
static void FillBuffer(FILE *fp, char *buffer);
void *CountingSort(void *args);
void DestroyThreads(pthread_t *arr_threads);				 

void *Test(void *args);

int main()
{
	size_t i = 0;
	
	size_t size_of_segment = 0;
	
	char *buffer = NULL;
	
	pthread_t arr_threads[NUM_OF_THREADS] = {0};
	
	thread_args_t *thread_args[NUM_OF_THREADS];

	if (NULL == CreateBigData(buffer, &size_of_segment))
	{
		return -1;
	}
	
	/*start timer*/
	
	/*each thread uses counting sort on one segment of the big buffer*/
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		thread_args[i]->sub_seg_size = size_of_segment;
		thread_args[i]->range = LETTERS_IN_ABC;
		thread_args[i]->sub_segment = buffer + i * thread_args[i]->sub_seg_size;		
		
		pthread_create(&(arr_threads[i]), NULL, Test, thread_args[i]);
	}
	
	DestroyBigData(buffer);
	
	/*join all threads and free mallocs*/
	DestroyThreads(arr_threads);
	
	/*get end time*/
	
	return 0;
}	



char *CreateBigData(char *buffer, size_t *size_of_segment)
{
	FILE *fp = fopen(DICT_PATH , "r");

	size_t letters_in_dict = CountLetters(fp);
	
	*size_of_segment = letters_in_dict / NUM_OF_THREADS;
	
	buffer = (char *)calloc(letters_in_dict, sizeof(char *));
	if (NULL == buffer)
	{
		return NULL;
	}
	
	FillBuffer(fp, buffer);
	
	/*duplicate dict buffer*/
	buffer = realloc(buffer, BIG_DATA * letters_in_dict * sizeof(char *));
	if (NULL == buffer)
	{
		free(buffer);
		return NULL;
	}
	
	fclose(fp);
	
	return buffer;
}

void DestroyBigData(char *buffer)
{
	free(buffer);
}


void DestroyThreads(pthread_t *arr_threads)
{
	size_t i = 0;
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(arr_threads[i], NULL);
	}
}



static size_t CountLetters(FILE *fp)
{
	size_t counter = 0;
	
	assert(NULL != fp);
	
	while (0 == feof(fp))
	{
		counter += 1 * (0 != isalpha(fgetc(fp)));
	}	

	return counter;
}

static void FillBuffer(FILE *fp, char *buffer)
{
	char ch = 0;
	
	assert(NULL != fp);
	
	rewind(fp);
	
	while (0 == feof(fp))
	{
		ch = fgetc(fp);
		
		if (isalpha(ch))
		{
			*buffer = ch;
			++buffer;
		}
	}	
}

void *Test(void *args)
{
	return NULL;
}


void *CountingSort(void *args)
{
	thread_args_t *input = (thread_args_t *)args;
	
	char *input_arr = input->sub_segment;
	size_t iter = 0;
	size_t range = input->range;
	size_t arr_size = input->sub_seg_size;
	
	size_t *hist = NULL;
	
	/*alloc memory for histogram*/
	hist = (size_t *)calloc(range, sizeof(size_t));
	if(NULL == hist)
	{
		return NULL;
	}
	
	/*create histogram*/
	while(iter < arr_size)
	{
		++hist[ input_arr[iter] - 1 ];
		++iter;
	}
	
	/*makes prefix sum from the histogram array*/
	for(iter = 0; iter < range - 1; iter++)
	{
		hist[iter + 1] += hist[iter];
	}
	
	/*placing the integer from the input arr, in its correct place 
	  inside the sorted array, according to the histogram*/
	for(iter = 0; iter < arr_size; iter++)
	{		
		/*sorted_arr[ hist[ input_arr[iter] - 1 ] -1 ] += input_arr[iter];*/
		
		--hist[ input_arr[iter] - 1 ];
	}	
	
	free(hist);
	
	return (0);
}
