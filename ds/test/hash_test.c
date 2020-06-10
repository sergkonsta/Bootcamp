

#include <stdio.h>
#include <ctype.h>	/*for tolower*/
#include <string.h>	/*for strcmp*/

#include "hash.h"

#define DICT_PATH ("/usr/share/dict/american-english")
#define LONGEST_WORD_SIZE 30
#define HASH_TABLE_SIZE (1000) 

#define UNUSED(X) (void)(X)

#define ERROR (printf("\nError in line: %d",__LINE__))

size_t HashSimple(const void *key);
size_t HashDJB2(const void *data_2_insert);
int CmpString(const void *key_1, const void *key_2);
int Act(void *arg, void *act_func_param);
int IncrementSizetByOne(void *arg, void *num);
int DictTest(hash_t *table);
void SimpleTests(hash_t *table);

int main()
{
	hash_t *table = HashTableCreate(HashDJB2, CmpString, HASH_TABLE_SIZE);	
	size_t size = 0;
	
	char *str1 = "apple";
	char *str2 = "zero";
	char *str3 = "serg";
	char *str4 = "sun";
	char *str5 = "georgia";
	
	if(0 != HashTableSize(table))
	{
		ERROR;
	}
	
	if(1 != HashTableIsEmpty(table))
	{
		ERROR;
	}
		
	HashTableInsert(table, (void *)str1);
	HashTableInsert(table, (void *)str2);
	HashTableInsert(table, (void *)str3);
	HashTableInsert(table, (void *)str4);
	HashTableInsert(table, (void *)str5);
		
	if(NULL == HashTableFind(table, (void *)str1))
	{
		ERROR;
	}
	
	HashTableRemove(table, (void *)str1);
	
	if(NULL != HashTableFind(table, (void *)str1))
	{
		ERROR;
	}	
	
	if(0 != HashTableIsEmpty(table))
	{
		ERROR;
	}
	
	HashTableForEach(table, IncrementSizetByOne, &size);
	if(size != HashTableSize(table))
	{
		ERROR;
	}
	
	
	
	
	
	
	
	/*DictTest(table);*/

	HashTableDestroy(table);
	return (0);
}



int DictTest(hash_t *table)
{
	char string[LONGEST_WORD_SIZE] = "";
	char *str = string;
	char ch = '\0';
		
	FILE *file_pointer = fopen(DICT_PATH, "r");
		
	/*check every char for end of line char, while file not ended */
	while(0 == feof(file_pointer))
	{
		ch = fgetc(file_pointer);
		
		if(ch == '\n')
		{			
			*str = '\0';
			HashTableInsert(table, (void *)string);
			/*printf("\n%s\n",string);*/
			
			str = string;
			str = strcpy(str, "");
		}
		
		else
		{
			*str = ch;
			++str;
		}
	}		

	fclose(file_pointer);
	
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
	size_t hash = (tolower(*str) - 97 + 6) % HASH_TABLE_SIZE;
	
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
		hash = (((hash << 5) + hash) + c) % HASH_TABLE_SIZE;
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

