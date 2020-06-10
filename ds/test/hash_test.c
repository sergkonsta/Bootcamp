
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>	/*for tolower*/
#include <string.h>	/*for strcmp*/

#include "hash.h"

#define DICT_PATH ("/usr/share/dict/american-english")
#define UNUSED(X) (void)(X)
#define DICTIONARY_SIZE 102306
#define NUM_LETTERS_IN_ABC 26
#define ERROR (printf("\nError in line: %d",__LINE__))

size_t HashSimple(const void *key);
size_t HashDJB2(const void *data_2_insert);
int CmpString(const void *key_1, const void *key_2);
int Act(void *arg, void *act_func_param);
int IncrementSizetByOne(void *arg, void *num);
int DictTest(hash_t *table);
void SimpleTests(hash_t *table);
static hash_t *InitHashTable();
static int FreeData(void *data, void *arg);



int main()
{
	int i = 0;
	int param = 0;
	
	char buffer[30];
	
	hash_t *table = InitHashTable();
	
	if(HashTableSize(table) != DICTIONARY_SIZE)
	{
		ERROR;
	}
	
	while(i < 5)
	{
		printf("Enter a word...\n");
		fgets(buffer, 30, stdin);
		
		if (HashTableFind(table, buffer) != NULL)
		{
			printf("Word found\n");
		}
		else
		{
			printf("Not found\n");
		}
		
		++i;
	}
	
	HashTableForEach(table, FreeData, &param);
	
	HashTableDestroy(table);
	
	return 0;
}

	
	
static hash_t *InitHashTable()
{
	hash_t *table = HashTableCreate(HashSimple, CmpString, NUM_LETTERS_IN_ABC - 1);

	char *buffer = NULL;
	
	FILE *fp = fopen(DICT_PATH , "r");
	
	while (feof(fp) == 0)
	{
		buffer = calloc(30, 1);
		fgets(buffer, 30, fp);
		HashTableInsert(table, buffer);
	}
	
	fclose(fp);
	
	return table;
}	
	
static int FreeData(void *data, void *arg)
{
	UNUSED(arg);
	free(data);
	return 0;
}	

/*
sorts by letters. 
a gices index 0, 
z gives index 25
*/
size_t HashSimple(const void *data_2_insert)
{
	const char *str = data_2_insert;
	size_t hash = (tolower(*str) - 97 + 6);
	
	/*printf("\nindex for: %s is: %ld\n",str,hash);*/
	
	return hash;
}

/*djb2 hash func*/
size_t HashDJB2(const void *data_2_insert)
{
	size_t hash = 5381;
	int c = 0;
	const char *str = data_2_insert;
	
	while((c = *str++))
	{
		hash = (((hash << 5) + hash) + c);
	}
	
	return hash;
}

/*for dlist should work like is_match - true false*/
int CmpString(const void *key_1, const void *key_2)
{
	const char *str1 = key_1;
	const char *str2 = key_2;
	
	return !strcmp(str1, str2);
}

int Act(void *arg, void *act_func_param)
{
	UNUSED(arg);
	UNUSED(act_func_param);
	return 0;
}


int IncrementSizetByOne(void *arg, void *num)
{
	UNUSED(arg);
	
	++*(size_t *)num;
	
	return (0);
}

