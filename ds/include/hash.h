#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>

typedef size_t (*hash_func_t)(const void *data);
typedef int (*cmp_func_t)(const void *key_1, const void *key_2);
typedef int (*act_func_t)(void *arg, void *act_func_param);

typedef struct hash hash_t;



/*----------------------------------------------------------------------------*/
/*
O(1)
creates hash table struct
on success: returns pointer to hash_t  
on fail: NULL
udefined behavior: hash_func == NULL, table_size == 0
*/
hash_t *HashTableCreate(hash_func_t hash_func, cmp_func_t cmp_func, size_t table_size);

/*----------------------------------------------------------------------------*/
/*
O(1)
destroys hash table
on success: void
on fail: ---
udefined behavior: hash_func == NULL, size == 0
*/
void HashTableDestroy(hash_t *table);

/*----------------------------------------------------------------------------*/
/*
O(1)
function: inserts data into the table
on success: returns 0 for success 1 for failed insert
on fail: return NULL
udefined behavior: table == NULL
*/
int HashTableInsert(hash_t *table, void *data);

/*----------------------------------------------------------------------------*/
/*
O(1)
function: removes data from table
on success: ---
on fail: ---
udefined behavior: table == NULL
*/
void HashTableRemove(hash_t *table, const void *data);

/*----------------------------------------------------------------------------*/
/*
O(1)
function: find data in the table
on success: returns address to data in table, NULL if not found
on fail: ???
udefined behavior: table == NULL
*/
void *HashTableFind(const hash_t *table, const void *data);


/*----------------------------------------------------------------------------*/
/*
O(n)
function: checks amount of values in the table
on success: returns size of table
on fail: ---
udefined behavior: table == NULL
*/
size_t HashTableSize(const hash_t *table);


/*----------------------------------------------------------------------------*/
/*
O(1)
function: checks if table is empty
on success: returns 1 for empty 0 for not
on fail: ---
udefined behavior: table == NULL
*/
int HashTableIsEmpty(const hash_t *table);


/*----------------------------------------------------------------------------*/
/*
O(n)
function: applies act_func for each value
on success: returns act_func return value for success
on fail: returns act_func return value for failure
udefined behavior: table == NULL, must not change hash key
*/
int HashTableForEach(hash_t *table, act_func_t act_func, void *act_func_param);


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


#endif


