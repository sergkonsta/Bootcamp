
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      08.06.2020               **
**  Reviewer:  Irina Smolkin			**
**  Status:    Approved					**
*****************************************/
#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/
#include <math.h>	/*for pow*/

#include "dlist.h"
#include "hash.h"

struct hash
{
	hash_func_t hash_func;	
	cmp_func_t cmp_func;	
	size_t num_of_buckets;	
	dlist_t *arr[1]; 	/*flex array*/
};


/*----------------------------------------------------------------------------*/
/*
O(1)
creates hash table struct
on success: returns pointer to hash_t  
on fail: NULL
udefined behavior: cmp_func (or) hash_func == NULL, num_of_buckets == 0
*/
hash_t *HashTableCreate(hash_func_t hash_func, cmp_func_t cmp_func, size_t num_of_buckets)
{
	size_t i = 0;

	/*inits hash struct*/
	hash_t *table = NULL;
	
	/* -1 for 1 cell that exists in sizeof(hash_t)*/
	size_t size_2_alloc = ((sizeof(table->arr) * (num_of_buckets - 1)) + sizeof(hash_t));
	
	assert(NULL != hash_func);	
	assert(NULL != cmp_func);
	
	table = (hash_t *)malloc(size_2_alloc);
	if (NULL == table)
	{
		return NULL;
	}
	
	table->hash_func = hash_func;
	table->cmp_func = cmp_func;
	table->num_of_buckets = num_of_buckets;	
	
	/*inits dlists in every hash-table index*/
	for(; i < num_of_buckets; ++i)
	{
		table->arr[i] = DListCreate();
		if(NULL == table->arr[i])
		{
			table->num_of_buckets = i;
			HashTableDestroy(table);	
			return NULL;
		}
	}
	
	return table;
}



/*----------------------------------------------------------------------------*/
/*
O(1)
destroys hash table
on success: void
on fail: ---
udefined behavior: hash_func == NULL, size == 0
*/
void HashTableDestroy(hash_t *table)
{
	size_t i = 0;
	
	assert(NULL != table);
	
	/*iterate table cells*/
	for (; i < table->num_of_buckets; i++)
	{
		if (NULL != table->arr[i])
		{
			DListDestroy(table->arr[i]);
			table->arr[i] = NULL;
		}
	}

	free(table);

	table = NULL;
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function: inserts data into the table
on success: returns 0 for success 1 for failed insert
on fail: return NULL
udefined behavior: table == NULL
*/
int HashTableInsert(hash_t *table, void *data)
{
	size_t hash_index = 0;
	dlist_t *table_cell = NULL;
	
	assert(NULL != table);
	assert(NULL != table->arr);
		
	/*recieve index of container where to insert data*/
	hash_index = table->hash_func(data);
		
	/*get address of said container*/	
	table_cell = table->arr[hash_index % table->num_of_buckets]; 
	
	/*inserts data and checks if insertion successful*/
	return DListIsIterEqual(DListEnd(table_cell), DListInsert(DListBegin(table_cell), data));

}



/*----------------------------------------------------------------------------*/
/*
O(1)
function: removes data from table,
on success: void
on fail: ---
udefined behavior: table == NULL
*/
void HashTableRemove(hash_t *table, const void *data)
{
	size_t hash_index = 0;
	dlist_t *table_cell = NULL;
	void *to_remove = NULL;
		
	assert(NULL != table);
	
	hash_index = table->hash_func(data);	
	
	table_cell = table->arr[hash_index % table->num_of_buckets];	
		
	to_remove = DListFind(DListBegin(table_cell), DListEnd(table_cell), table->cmp_func, data);
	if(!DListIsIterEqual(to_remove, DListEnd(table_cell)))
	{
		DListRemove(to_remove);
	}
}



/*----------------------------------------------------------------------------*/
/*
O(1)
function: find data in the table
on success: returns address to data in table, NULL if not found
on fail: ---
udefined behavior: table == NULL
*/
void *HashTableFind(const hash_t *table, const void *data)
{
	size_t hash_index = 0;
	dlist_t *table_cell = NULL;
	void *iter_found = NULL; 
	void *ret_data = NULL;
		
	assert(NULL != table);
	
	hash_index = table->hash_func(data);	
	
	table_cell = table->arr[hash_index % table->num_of_buckets];
		
	iter_found = DListFind(DListBegin(table_cell), DListEnd(table_cell), 
					  table->cmp_func, data);
	
	if (DListIsIterEqual(iter_found, DListEnd(table_cell)))
	{
		return NULL;
	}
	
	ret_data = DListGetData(iter_found);
		
	if (NULL != DListPushFront(table_cell, ret_data))
	{
		DListRemove(iter_found);
	}	
		
	return ret_data;
}


/*----------------------------------------------------------------------------*/
/*
O(n)
function: checks amount of values in the table
on success: returns size of table
on fail: ---
udefined behavior: table == NULL
*/
size_t HashTableSize(const hash_t *table)
{
	size_t i = 0;
	size_t size = 0;
	
	assert(NULL != table);

	/*iterate hash table and count datas in every bucket*/
	for(; i < table->num_of_buckets; ++i)
	{
		size += DListCount(table->arr[i]);
	}
		
	return size;
}

/*----------------------------------------------------------------------------*/
/*
O(1) - iterates through every index in flex array and checks if dlist is empty
	   table size is not dependant on the input.
	   
function: checks if table is empty
on success: returns 1 for empty 0 for not
on fail: ---
udefined behavior: table == NULL
*/
int HashTableIsEmpty(const hash_t *table)
{
	size_t i = 0;
	
	assert(NULL != table);

	/*iterate hash table and check if every bucket is empty*/
	for(; i < table->num_of_buckets; ++i)
	{
		if(0 == DListIsEmpty(table->arr[i]))
		{
			return 0;
		}
	}
		
	return 1;
}


/*----------------------------------------------------------------------------*/
/*
O(n)
function: applies act_func for each value
on success: returns act_func return value for success
on fail: returns act_func return value for failure
udefined behavior: table == NULL, must not change hash key
*/
int HashTableForEach(hash_t *table, act_func_t act_func, void *act_func_param)
{
	size_t i = 0;
	int status = 0;
	
	assert(NULL != table);
	assert(NULL != act_func);
	
	/*iterate hash table and perform for each on every data in every bucket*/
	for(; i< table->num_of_buckets; i++)
	{
		status = DListForEach(DListBegin(table->arr[i]), DListEnd(table->arr[i]), 
							  act_func, act_func_param); 
		if(0 != status)
		{
			return status;	
		}
	}
		
	return status;
}


/*------------------------------ADVANCE---------------------------------------*/
/*
O(n)
function: gets table standart deviation
on success: 
on fail: 
udefined behavior: table == NULL
*/
double HashTableSD(const hash_t *table)
{
	double avg = 0;
	double sum_of_deviation = 0;
	size_t i = 0;

	assert(NULL != table);

	avg = HashTableLoad(table);

	for (i = 0; i < table->num_of_buckets; ++i)
	{
		sum_of_deviation += pow(DListCount(table->arr[i]) - avg, 2);
	}	

	return pow(sum_of_deviation, 0.5);
}


/*------------------------------ADVANCE---------------------------------------*/
/*
O(n)
function: gets table load factor
on success: 
on fail: 
udefined behavior: table == NULL
*/
double HashTableLoad(const hash_t *table)
{
	assert(NULL != table);

	return ((HashTableSize(table) / table->num_of_buckets));
}


