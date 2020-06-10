
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      08.06.2020               **
**  Reviewer:  Irina Smolkin			**
**  Status:    ???						**
*****************************************/
#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/

#include "hash.h"
#include "dlist.h"

struct hash
{
	hash_func_t hash_func;	
	cmp_func_t cmp_func;	
	size_t table_size;	/* total number of indexes*/	
	dlist_t *arr[1]; 	/*flex array*/
};

static int InitTableCellsImp(dlist_t **arr, size_t table_size);

/*----------------------------------------------------------------------------*/
/*
O(1)
creates hash table struct
on success: returns pointer to hash_t  
on fail: NULL
udefined behavior: cmp_func (or) hash_func == NULL, table_size == 0
*/
hash_t *HashTableCreate(hash_func_t hash_func, cmp_func_t cmp_func, size_t table_size)
{
	size_t i = 0;

	/*inits hash struct*/
	hash_t *table = NULL;
	
	/* -1 for 1 cell that exists in sizeof(hash_t)*/
	size_t size_2_alloc = ((sizeof(table->arr) * (table_size - 1)) + sizeof(hash_t));
	
	assert(NULL != hash_func);	
	assert(NULL != cmp_func);
	
	table = (hash_t *)malloc(size_2_alloc);
	if(NULL == table)
	{
		return NULL;
	}
	
	table->hash_func = hash_func;
	table->cmp_func = cmp_func;
	table->table_size = table_size;	
	
	/*inits dlists in every hash-table index*/
	for(; i < table->table_size; i++)
	{
		table->arr[i] = DListCreate();
		if(NULL == table->arr[i])
		{
			HashTableDestroy(table);
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
	for(; i < table->table_size; i++)
	{
		if(NULL != table->arr[i])
		{
			DListDestroy(table->arr[i]);
		}
	}

	free(table);
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
		
	/*recieve index of container where to insert data*/
	hash_index = table->hash_func(data);
	
	assert(hash_index < table->table_size);
	
	/*get address of said container*/	
	table_cell = table->arr[hash_index];	
	
	/*inserts data and checks if insertion successful*/
	if(1 != DListIsIterEqual(DListEnd(table_cell), DListInsert(DListBegin(table_cell), data)))
	{
		return 1;
	}
	
	return 0;	
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
	void *data_address = NULL;
	
	assert(NULL != table);
	
	/*get datas address using hashfind, return if not found*/
	data_address = HashTableFind(table, data);
	if(NULL == data_address)
	{
		return;
	}
	
	/*remove using dlist remove*/
	DListRemove(data_address);
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
		
	assert(NULL != table);
	
	/*recieve index of container where to insert data*/
	hash_index = table->hash_func(data);
	
	assert(hash_index < table->table_size);
	
	/*get address of said container*/	
	table_cell = table->arr[hash_index];
		
	return (DListFind(DListBegin(table_cell), DListEnd(table_cell), 
					  table->cmp_func, data));
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
	for(; i< table->table_size; i++)
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
	for(; i< table->table_size; i++)
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

	assert(NULL != table);
	assert(NULL != act_func);
	
	/*iterate hash table and perform for each on every data in every bucket*/
	for(; i< table->table_size; i++)
	{
		if(0 != DListForEach(DListBegin(table->arr[i]), DListEnd(table->arr[i]), 
							 act_func, act_func_param))
		{
			return 1;
		}
	}
		
	return 0;
}


/*------------------------------ADVANCE---------------------------------------*/
/*
O(n)
function: gets table standart deviation
on success: 
on fail: 
udefined behavior: table == NULL
*/
double HashTableSD(const hash_t *table);



/*------------------------------ADVANCE---------------------------------------*/
/*
O(n)
function: gets table load factor
on success: 
on fail: 
udefined behavior: table == NULL
*/
double HashTableLoad(const hash_t *table);


