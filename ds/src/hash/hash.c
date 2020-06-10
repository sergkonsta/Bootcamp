
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
static int HashTableDestroyImp(dlist_t **table_cell, size_t table_size);
static size_t HashTableSizeImp(const dlist_t **table_cell, size_t table_size, size_t size);
static size_t HashTableIsEmptyImp(const dlist_t **table_cell, size_t table_size);
static int HashTableForEachImp(const dlist_t **table_cell, size_t table_size, 
								  act_func_t act_func, void *act_func_param);
static void *HashTableFindImp(const dlist_t **table_cell, size_t table_size, 
							  cmp_func_t cmp_func, const void *data_2_find, void *found);
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
	table->arr[0] = NULL;
	
	/*inits dlists in every hash-table index*/
	if(1 == InitTableCellsImp(table->arr, table->table_size))
	{
		free(table);
		return NULL;
	}	
	
	return table;
}



/*	function:	recursively initializes hash table cells
	returns:	0 for success; 1 for failure						*/
static int InitTableCellsImp(dlist_t **table_cell, size_t table_size)
{
	/*stop - end of hash table*/
	if(0 == table_size)
	{
		return 0;
	}
	
	/*create dlist*/
	*table_cell = DListCreate();
	if(NULL == *table_cell)
	{
		return 1;
	}
		
	/*going down recursion: calls next table cell
	  going back up:		destroys everything if dlist creation failed*/
	if( 0 == InitTableCellsImp( 
		(dlist_t **)((char *)table_cell + sizeof(*table_cell)), table_size - 1))
	{
		return 0;
	}	

	DListDestroy(*table_cell);
	
	return 1;	
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
	assert(NULL != table);
	
	HashTableDestroyImp(table->arr, table->table_size);

	/*destroys hash table struct*/
	table->hash_func = NULL;
	table->cmp_func = NULL;
	table->table_size = 0;
	
	free(table);
}


/*	function:	tail rec - recursively destroys hash table cells
	returns:	---										*/
static int HashTableDestroyImp(dlist_t **table_cell, size_t table_size)
{
	/*stop - end of hash table*/
	if(0 == table_size)
	{
		return 0;
	}
	
	/*destroys one dlist*/
	DListDestroy(*table_cell);
		
	/*going down recursion: calls next table cell*/
	return(HashTableDestroyImp(
	(dlist_t **)((char *)table_cell + sizeof(*table_cell)), table_size - 1));	
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
	
	/*get address of said container*/	
	table_cell = table->arr[hash_index];

	/*inserts data and checks if insertion successful*/
	if(DListEnd(table_cell) == DListInsert(DListBegin(table_cell), data))
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
	void *found = NULL;
		
	assert(NULL != table);
	
	return (HashTableFindImp((const dlist_t **)table->arr, table->table_size, 
							 table->cmp_func, data, found));
}

/*	function:	tail rec - recursively ???
	returns:	????							*/
static void *HashTableFindImp(const dlist_t **table_cell, size_t table_size, 
							  cmp_func_t cmp_func, const void *data_2_find, void *found)
{	
	/*stop - end of hash table*/
	if(0 == table_size)
	{
		return NULL;
	}
	
	found = DListFind(DListBegin(*table_cell), DListEnd(*table_cell), 
					  cmp_func, data_2_find); /*DListFind might return 1 after tail!!!!! need to fix*/
					  
	if(DListGetData(found) == data_2_find)
	{
		return found;
	}
		
	/*going down recursion: calls next table cell*/
	return HashTableFindImp(
	(const dlist_t **)((char *)table_cell + sizeof(*table_cell)), 
	table_size - 1, cmp_func, data_2_find, found);	
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
	assert(NULL != table);	
	
	return HashTableSizeImp((const dlist_t **)table->arr, table->table_size, 0);
}


/*	function:	tail rec - recursively counts data in all hash table cells
	returns:	amount of data values in table										*/
static size_t HashTableSizeImp(const dlist_t **table_cell, size_t table_size, size_t size)
{
	/*stop - end of hash table*/
	if(0 == table_size)
	{
		return size;
	}
	
	/*checks size one dlist*/
	size += DListCount(*table_cell);
		
	/*going down recursion: calls next table cell*/
	return HashTableSizeImp(
	(const dlist_t **)((char *)table_cell + sizeof(*table_cell)), table_size - 1, size);	
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
	assert(NULL != table);
	
	return HashTableIsEmptyImp((const dlist_t **)table->arr, table->table_size);
}

/*	function:	tail rec - recursively checks all hash table cells are empty
	returns:	1 for empty, 0 for not empty, 
				returns at first unempty cell							*/
static size_t HashTableIsEmptyImp(const dlist_t **table_cell, size_t table_size)
{
	/*stop - end of hash table*/
	if(0 == table_size)
	{
		return 1;
	}
	
	/*checks if one container is empty*/
	if(1 != DListIsEmpty(*table_cell))
	{
		return 0;
	}
		
	/*going down recursion: calls next table cell*/
	return HashTableIsEmptyImp(
	(const dlist_t **)((char *)table_cell + sizeof(*table_cell)), table_size - 1);	
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
	assert(NULL != table);
	assert(NULL != act_func);
	
	return HashTableForEachImp((const dlist_t **)table->arr, table->table_size, 
								act_func, act_func_param);
}


/*	function:	tail rec - recursively applies DlistForEach on each hash table cell
	returns:	0 for successful applications, 1 for failure 
				returns at first failed action func							*/
static int HashTableForEachImp(const dlist_t **table_cell, size_t table_size, 
								  act_func_t act_func, void *act_func_param)
{
	/*stop - end of hash table*/
	if(0 == table_size)
	{
		return 1;
	}
	
	/*checks if action func failed*/
	if(1 == DListForEach(DListBegin(*table_cell), DListEnd(*table_cell), 
						 act_func, act_func_param))
	{
		return 1;
	}
		
	/*going down recursion: calls next table cell*/
	return HashTableForEachImp(
	(const dlist_t **)((char *)table_cell + sizeof(*table_cell)), 
	table_size - 1, act_func, act_func_param);	
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


