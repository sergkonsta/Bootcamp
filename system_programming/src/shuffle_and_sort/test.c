

#include <stdlib.h>		/* calloc */
#include <stdio.h>		/* print, fopen */
#include <assert.h>		/* assert */
#include <ctype.h>		/* isalpha */
#include <pthread.h>	/* pthread */
#include <string.h>		/* memcpy */
#include <sys/timeb.h>	/* ftime */

#define DICT_PATH ("/usr/share/dict/american-english")
#define WORDS_IN_DICT (102306)
#define LETTERS_IN_ABC (26)
#define MAX_THREADS (20)
#define BIG_DATA (2)	
#define NEW_LINE_ASCII (10)
#define LONG_WORD (30)

char **CreateBigData(char **p_big_data);
static int FillBuffer(char **p_big_data, FILE *fp);
static size_t CountWords(FILE *fp);



int main()
{
	
	size_t i = 0;
	char **p_big_data = CreateBigData(p_big_data);
	
	if (NULL == p_big_data)
	{
		printf("\nERROR\n");
	}	
	
	
	
	for (i = 0; i < WORDS_IN_DICT * BIG_DATA; ++i)
	{
		printf("%s\n",(*p_big_data) + i);
	}
	

}


char **CreateBigData(char **p_big_data)
{
	FILE *fp = fopen(DICT_PATH , "r");

	/*calloc amount of words in dict * big data multiplier*/
	p_big_data = (char **)calloc(CountWords(fp) * BIG_DATA, sizeof(char *));
	if (NULL == p_big_data)
	{
		return (NULL);
	}
	
	FillBuffer(p_big_data, fp);
	
	
	
	
	
	fclose(fp);
	fp = NULL;
	
	return (p_big_data);
}

static int FillBuffer(char **p_big_data, FILE *fp)
{
	char **start = p_big_data;
	size_t i = 0;
	
	assert(NULL != fp);
	assert(NULL != p_big_data);
	
	rewind(fp);
	
	while (0 == feof(fp))
	{
		*p_big_data = (char *)calloc(LONG_WORD, sizeof(char));
		if (NULL == *p_big_data)
		{
			return (-1);
		}
		
		fgets(*p_big_data, LONG_WORD, fp);

		++*(p_big_data);
	}
	

	
	/*for (i = 0; i < BIG_DATA; ++i, *p_big_data += WORDS_IN_DICT)
	{
		memcpy(p_big_data, start,WORDS_IN_DICT);
	}*/
	
	return 0;
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
