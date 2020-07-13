/*
Project:	Multithreading count sort
Developer:	Sergey Konstantinovsky
Date:		12/07/2020
*/

#include <stdlib.h>		/* calloc */
#include <stdio.h>		/* print, fopen */
#include <assert.h>		/* assert */
#include <ctype.h>		/* isalpha */
#include <pthread.h>	/* pthread */
#include <string.h>		/* memcpy */
#include <sys/timeb.h>	/* ftime */

#define DICT_PATH ("/usr/share/dict/american-english")
#define DICTIONARY_SIZE (102306)
#define LETTERS_IN_ABC (26)
#define MAX_THREADS (20)
#define BIG_DATA (222)	

#define FTIME ((end_time_ms.time * 1000 + end_time_ms.millitm) -\
				(start_time_ms.time * 1000 + start_time_ms.millitm))

typedef struct thread_args
{
	char *sub_segment;
	size_t range;
	size_t sub_seg_size;
} thread_args_t;

int MultiThreadBenchmark();
char *CreateBigData(char *buffer, size_t *size_of_segment);
void DestroyBigData(char *buffer);
static size_t CountLetters(FILE *fp);
static void FillBuffer(FILE *fp, char *buffer);
void *CountingSort(void *args);
void DestroyThreads(pthread_t *arr_threads);				 

size_t g_num_of_threads = 1;

int main()
{
	for (g_num_of_threads = 1; 
		MAX_THREADS > g_num_of_threads; 
		++g_num_of_threads)
	{
		MultiThreadBenchmark();
	}
	
	return (0);
}


int MultiThreadBenchmark()
{
	struct timeb start_time_ms;
	struct timeb end_time_ms;
	
	size_t i = 0;
	size_t size_of_segment = 0;
	char *buffer = NULL;
	
	pthread_t *arr_threads = 
	(pthread_t *)calloc(g_num_of_threads, sizeof(pthread_t));
	
	thread_args_t *thread_args = 
	(thread_args_t *)calloc(g_num_of_threads, sizeof(thread_args_t));

	buffer =  CreateBigData(buffer, &size_of_segment);
	if (NULL == buffer)
	{
		return (-1);
	}
	
	ftime(&start_time_ms);
	
	for (i = 0; i < g_num_of_threads; ++i)
	{
		thread_args[i].sub_seg_size = size_of_segment;
		thread_args[i].range = LETTERS_IN_ABC;
		thread_args[i].sub_segment = (buffer + i * size_of_segment);		
		
		pthread_create((arr_threads + i), NULL, CountingSort, (thread_args + i));
	}
	
	DestroyThreads(arr_threads);
	
	ftime(&end_time_ms);
	
	DestroyBigData(buffer);
	
	free(arr_threads);
	arr_threads = NULL;
	free(thread_args);
	thread_args = NULL;
	
	printf("\nNum of threads: %lu.\nTime elapsed: %ld[mSec].\n\n"
										,g_num_of_threads,FTIME);
										
	return (0);
}	



char *CreateBigData(char *buffer, size_t *size_of_segment)
{
	FILE *fp = fopen(DICT_PATH , "r");

	size_t letters_in_dict = CountLetters(fp);
	size_t i = 0;
	
	*size_of_segment = letters_in_dict / g_num_of_threads;
	
	buffer = (char *)calloc(letters_in_dict, sizeof(char));
	if (NULL == buffer)
	{
		return (NULL);
	}
	
	FillBuffer(fp, buffer);
	
	/*duplicate dict buffer*/
	buffer = (char *)realloc(buffer, BIG_DATA * letters_in_dict * sizeof(char));
	if (NULL == buffer)
	{
		return (NULL);
	}
	
	for (i = 0; i < BIG_DATA; ++i)
	{
		memcpy(buffer + (i * letters_in_dict), buffer, letters_in_dict);
	}
	
	fclose(fp);
	fp = NULL;
	
	return (buffer);
}

void DestroyBigData(char *buffer)
{
	free(buffer);
}


void DestroyThreads(pthread_t *arr_threads)
{
	size_t i = 0;
	for (i = 0; i < g_num_of_threads; ++i)
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

	return (counter);
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


void *CountingSort(void *args)
{
	thread_args_t *input = (thread_args_t *)args;
	
	char *input_arr = input->sub_segment;
	size_t iter = 0;
	size_t range = input->range;
	size_t arr_size = input->sub_seg_size;
	
	int *hist = NULL;
	
	char *sorted_arr = (char *)calloc(arr_size, sizeof(char));
	if (NULL == sorted_arr)
	{
		return (NULL);
	}
	
	hist = (int *)calloc(range, sizeof(int));
	if (NULL == hist)
	{
		free(sorted_arr);
		sorted_arr = NULL;
		return (NULL);
	}
	
	/* create histogram */
	while (iter < arr_size)
	{
		++hist[tolower(input_arr[iter]) - 97];
		++iter;
	}
	
	/* makes prefix sum from the histogram array */
	for (iter = 0; iter < range - 1; iter++)
	{
		hist[iter + 1] += hist[iter];
	}
	
	/* placing the integer from the input arr, in its correct place 
	  inside the sorted array, according to the histogram */
	for (iter = 0; iter < arr_size; iter++)
	{		
		sorted_arr[ hist[tolower(input_arr[iter]) - 97] - 1] = input_arr[iter];
		
		--hist[tolower(input_arr[iter]) - 97];
	}
	
	memcpy(input_arr, sorted_arr, arr_size);
	
	free(sorted_arr);
	sorted_arr = NULL;
	
	free(hist);
	hist = NULL;
	
	return (0);
}



