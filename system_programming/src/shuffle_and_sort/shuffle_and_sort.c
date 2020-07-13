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
#include <sys/types.h>	/*for ssize_t*/

#define DICT_PATH ("/usr/share/dict/american-english")
#define WORDS_IN_DICT (102306)
#define LETTERS_IN_ABC (26)
#define MAX_THREADS (20)
#define BIG_DATA (5)	
#define NEW_LINE_ASCII (10)
#define LONG_WORD (30)

#define FTIME ((end_time_ms.time * 1000 + end_time_ms.millitm) -\
				(start_time_ms.time * 1000 + start_time_ms.millitm))

#define UNUSED(X) (void)(X)

static char **InitWords();
static char **InitBigData(char **dict_words);
static size_t CountWords(FILE *fp);
static int RandomShuffleFunc(const void *a, const void *b);

int main()
{
	size_t i = 0;
	
	char **dict_words = InitWords();
	char **p_big_data = InitBigData(dict_words);
	
	/*random shuffle*/
	qsort((void *)p_big_data, WORDS_IN_DICT * BIG_DATA, sizeof(char *),
		 											RandomShuffleFunc);
	
	
	
	
	
	/*test print*/
	for (i = 0; i < WORDS_IN_DICT * BIG_DATA; ++i)
	{
		printf("%p\n",p_big_data[i]);
	}
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

	/* create array of pointers for big data */
	char **p_big_data = calloc(WORDS_IN_DICT * BIG_DATA, sizeof(char *));
	if (NULL == p_big_data)
	{
		return (NULL);
	}
	
	/* fill array of pointers */
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


static size_t CountWords(FILE *fp)
{
	size_t counter = 0;
	
	assert(NULL != fp);
	
	while (0 == feof(fp))
	{
		counter += 1 * (NEW_LINE_ASCII == fgetc(fp));
	}	

	return (counter);
}



