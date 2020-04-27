#ifndef __OL87_SORTED_LIST_H__
#define __OL87_SORTED_LIST_H__

#include <stddef.h> /*size_t*/

#include "dlist.h" /*dlist_t dlist_iter_t*/

typedef struct sort_list sort_list_t;

typedef struct sort_list_iter
{
	dlist_iter_t iter;

	/* only in debug version*/
	#ifndef NDEBUG
	sort_list_t *list; 
	#endif /* NDEBUG */
	
} sort_list_iter_t;


/*is_before - return 1 when data1 before data2. return 0 when equal or after */

/*
O(1) 
Create sorted list. 
return pointer to sorted_list or NULL if fails.
*/
sort_list_t *SortListCreate
	(int (*is_before)(const void *data1, const void *data2));	

	
/*
O(n) 
Destroy sorted list
*/
void SortListDestroy(sort_list_t *list);


/* 
O(n) 
Success: Retrun iter to inserted data. 
Fail: retun End 
*/
sort_list_iter_t SortListInsert(sort_list_t *list, void *data);


/* 
O(1) 
Return iter to next iterator 
*/
sort_list_iter_t SortListRemove(sort_list_iter_t iter);

/* 
O(n) 
Count of valid nodes in list 
*/
size_t SortListCount(const sort_list_t *list);


/* 
O(1) 
Return True if list is empty 
*/
int SortListIsEmpty(const sort_list_t *list);


/* 
O(1) 
Return TRUE if two iterators are the same 
*/
int SortListIsIterEqual(sort_list_iter_t iter_1, sort_list_iter_t iter_2);


/*
O(1)
first valid node (or End if empty) 
*/
sort_list_iter_t SortListBegin(sort_list_t *list);


/*
O(1)
return End of list
*/
sort_list_iter_t SortListEnd(sort_list_t *list);


/*
O(1)
Return next itertator 
Iter given MUST BE DIFFERENT then End 
*/
sort_list_iter_t SortListNext(sort_list_iter_t iter);


/*
O(1)
Return previous itertator 
Iter given MUST BE DIFFERENT then Begin 
*/
sort_list_iter_t SortListPrev(sort_list_iter_t iter);



/*
O(1) 
Return void pointer to data
*/
void *SortListGetData(sort_list_iter_t iter);


/* 
O(1)
Pop first value in list. 
Return next iterrator. 
List must not be Empty 
*/
sort_list_iter_t SortListPopFront(sort_list_t *list);


/* 
O(1)
Pop last valid value in list. 
Return End. 
List must not be Empty 
*/
sort_list_iter_t SortListPopBack(sort_list_t *list);


/*
O(n) 
Search Range "from"-"to"(exclusive)
Return first node found.
Return "to" if not found.
"from" and "to" must be from same list. 
*/
sort_list_iter_t SortListFind(const sort_list_t *list, sort_list_iter_t from, 
	sort_list_iter_t to, const void *param);


/*
O(n) 
Search Range "from"-"to"(exclusive)
Return first node found by is_equal.
Return "to" if not found.
"from" and "to" must be from same list. 
*/
sort_list_iter_t SortListFindIf(sort_list_iter_t from, sort_list_iter_t to,
	int (*is_equal)(const void *data, const void *param), const void *param);


/*
O(n)
Apply action_func on every node in Range "from"-"to"(exclusive).
If status returned from action_func != 0, stop and return status.
When done return last status returned by action_func.
action_func must not change original order of sorted data.
*/
int SortListForEach(sort_list_iter_t from, sort_list_iter_t to,
	int(*action_func)(void *data, void *arg), void *arg);


/*
O(n + m)  
Merge two sorted-lists into one. Return pointer to dest.
after merge source_list is empty(source list is not destroyed.) 
*/
sort_list_t *SortListMerge(sort_list_t *dest_list, sort_list_t *source_list);


#endif /*__OL87_SORTED_LIST_H__*/
