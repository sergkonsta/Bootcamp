#include <stdlib.h>	/*calloc*/
#include <stdio.h>	/*print, fopenqq*/
#include <assert.h>	/*assert*/
#include <ctype.h>	/*isalpha*/
	
#define DICT_PATH ("/usr/share/dict/american-english")
#define UNUSED(X) (void)(X)
#define DICTIONARY_SIZE (102306)
#define LETTERS_IN_ABC (26)
#define NUM_OF_THREADS (2)
#define BIG_DATA (100)	

static size_t CountLetters(FILE *fp);
static void FillBuffer(FILE *fp, char *buffer);

static int InitDictionaryBuffer(void)
{
	FILE *fp = fopen(DICT_PATH , "r");

	char *buffer = NULL;
	
	size_t i = 0;
	size_t letters_in_dict = CountLetters(fp);
	
	buffer = (char *)calloc(letters_in_dict, sizeof(char *));
	if (NULL == buffer)
	{
		return -1;
	}
	
	FillBuffer(fp, buffer);
	
	/*duplicate dict buffer*/
	buffer = realloc(buffer, BIG_DATA * letters_in_dict * sizeof(char *));
	if (NULL == buffer)
	{
		free(buffer);
		return -1;
	}
	
	/*create AMOUNT OF THREADS*/
	
	
	/*each thread uses counting sort on one buffer*/
	/**/

	
	/*	
	FILE *fp = fopen(DICT_PATH , "r");
	
	while (0 == feof(fp))
	{
		fgets(*dict_buffer, 30, fp);
		
				
	}
	
	fclose(fp);
	
	return table;
	*/
	
	free(buffer);
}	

int main()
{
	InitDictionaryBuffer();
	
	return 0;
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
