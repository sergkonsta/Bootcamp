/*
Project:	Multithreading count sort
Developer:	Sergey Konstantinovsky
Date:		12/07/2020
*/

#include <stdlib.h>		/* calloc, qsort, rand */
#include <stdio.h>		/* print, fopen */
#include <assert.h>		/* assert */
#include <ctype.h>		/* isalpha */
#include <pthread.h>	/* pthread */
#include <string.h>		/* memcpy */
#include <sys/timeb.h>	/* ftime */
#include <time.h>		/* clock_getttime*/

#define DICT_PATH ("/usr/share/dict/american-english")
#define WORDS_IN_DICT (102306)
#define LETTERS_IN_ABC (26)
#define BIG_DATA (100)	
#define LONG_WORD (30)

#define UNUSED(X) (void)(X)


typedef struct thread_args
{
	char **sub_segment;
	size_t sub_seg_size;
} thread_args_t;


static char **InitWords();
static char **InitBigData(char **dict_words);
static int RandomShuffleFunc(const void *a, const void *b);

static int SortSubArraysWithThreads(char **p_big_data);
static void *ThreadQSort(void *args);
static int SortCmpFunc(const void *a, const void *b);

static int MergeImp(char **arr, size_t l, size_t m, size_t r);
												   
size_t g_num_of_threads = 1;


int main()
{
	char **dict_words = InitWords();
	char **p_big_data = InitBigData(dict_words);
	
	double time = 0.0;
	
	struct timespec requestStart, requestEnd;
	
	/*test from 1 to 256 threads*/
	for (; g_num_of_threads <= 256; g_num_of_threads *= 2)
	{
		clock_gettime(CLOCK_REALTIME, &requestStart);
		
		/*random shuffle*/
		qsort((void *)p_big_data, WORDS_IN_DICT * BIG_DATA, sizeof(char *),
				RandomShuffleFunc);
		
		SortSubArraysWithThreads(p_big_data);
			
		MergeImp(p_big_data, 0, WORDS_IN_DICT * BIG_DATA / 2, WORDS_IN_DICT * BIG_DATA);
		
		clock_gettime(CLOCK_REALTIME, &requestEnd);
	
		time = ( requestEnd.tv_sec - requestStart.tv_sec ) + 
				( requestEnd.tv_nsec - requestStart.tv_nsec ) / 1E9;
		printf("\n%lu threads finished in: %f time.\n",g_num_of_threads,time);
	}
		
	return (0);
}


static int SortSubArraysWithThreads(char **p_big_data)
{
	size_t i = 0;
	size_t size_of_segment = BIG_DATA * WORDS_IN_DICT;

	pthread_t *arr_threads = 
	(pthread_t *)calloc(g_num_of_threads, sizeof(pthread_t));
	
	thread_args_t *thread_args = 
	(thread_args_t *)calloc(g_num_of_threads, sizeof(thread_args_t));
	
	for (i = 0; i < g_num_of_threads; ++i)
	{
		thread_args[i].sub_seg_size = size_of_segment / g_num_of_threads;
		
		thread_args[i].sub_segment = 
		p_big_data + i * thread_args[i].sub_seg_size;
		
		pthread_create((arr_threads + i), NULL, ThreadQSort, (thread_args + i));
	}
	
	/* destroy threads */
	for (i = 0; i < g_num_of_threads; ++i)
	{
		pthread_join(arr_threads[i], NULL);
	}
	
	free(arr_threads);
	arr_threads = NULL;
	
	free(thread_args);
	thread_args = NULL;
	
	return (0);
}	




static void *ThreadQSort(void *args)
{
	thread_args_t *input = (thread_args_t *)args;
	
	qsort((void *)input->sub_segment, input->sub_seg_size, 
							sizeof(char *), SortCmpFunc);
	
	return (NULL);
}

static int SortCmpFunc(const void *a, const void *b)
{
	return (strcmp(*(char **)a, *(char **)b));
}


static char **InitWords()
{
	size_t i = 0;
	
	FILE *fp = fopen(DICT_PATH , "r");

	/*calloc amount of words in dict * big data multiplier*/
	char **words = calloc(WORDS_IN_DICT * BIG_DATA, sizeof(char *));
	if (NULL == words)
	{
		return (NULL);
	}
	
	/*create strings and fill with words*/
	for (i = 0; i < WORDS_IN_DICT; ++i)
	{
		words[i] = (char *)calloc(LONG_WORD, sizeof(char));
		if (NULL ==  words[i])
		{
			return (NULL);
		}

		fgets(words[i], LONG_WORD, fp);
	}
	
	
	fclose(fp);
	fp = NULL;
	
	return (words);
}



static char **InitBigData(char **dict_words)
{
	size_t i = 0;

	/* create arr_to_sort of pointers for big data */
	char **p_big_data = calloc(WORDS_IN_DICT * BIG_DATA, sizeof(char *));
	if (NULL == p_big_data)
	{ 

		return (NULL);
	}
	
	/* fill arr_to_sort of pointers */
	for (i = 0; i < WORDS_IN_DICT * BIG_DATA; ++i)
	{
		p_big_data[i] = dict_words[i % WORDS_IN_DICT];
	}
	
	return (p_big_data);
}



/*return random number between -1 to 1*/
static int RandomShuffleFunc(const void *a, const void *b)
{
	int x = rand();
	
	UNUSED(a);
	UNUSED(b);
	
	return ((x > RAND_MAX / 2) * 1 +  (x < RAND_MAX / 2) * (-1));
}



static int MergeImp(char **arr, size_t l, size_t m, size_t r)
{
	size_t i, j, k; 
    size_t n1 = m - l + 1; 
    size_t n2 = r - m; 
  
  	char **L = (char **)calloc(n1, sizeof(char *));
	char **R = (char **)calloc(n2, sizeof(char *));
	if (NULL == L || NULL == R)
	{
		free(L);
		free(R);
		
		return 1;
	}
  
    for (i = 0; i < n1; i++) 
    {
        L[i] = arr[l + i];
    } 
    
    for (j = 0; j < n2; j++)
    { 
        R[j] = arr[m + 1 + j]; 
    }
  
    i = 0; 
    j = 0; 
    k = l; 
    
    while (i < n1 && j < n2 - 1) 
    { 
        if (0 >= strcmp(L[i], R[j]))
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        
        else 
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 

	return 0;
}


