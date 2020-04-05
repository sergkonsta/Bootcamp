/*---------------------------------------------------------------------------*/
/*MACROS FOR REST OF WORKSEET*/

#define MAX2(a, b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
      _a > _b ? _a : _b; })
                        
#define MAX3(a, b, c) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
      __typeof__ (c) _c = (c); \
      _c > MAX2(_a,_b) ? _c : MAX2(_a,_b); })

#define SIZEOF_VAR(object) 	(char *)(&object+1) - (char *)(&object)


#define SIZEOF_TYPE(var) ((size_t)(1 + (var*)0))
/*---------------------------------------------------------------------------*/

/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      31.03.2020               **
**  Reviewer:  Irina					**
**  Status:    Approved					**
*****************************************/

#include <stdio.h>	/*for printf*/
#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for strlen, strcpy, strcmp*/

/*amount of elements in array*/
#define INT_TO_ADD (12)
#define AMOUNT_OF_ELEMENTS (5)
#define NULL_CHAR_SIZE (1)
#define UNUSED(data) (void)(data)

/*defining function pointers for struct*/
typedef void (*Printfunc)();
typedef int (*Addfunc)();
typedef int (*Cleanup)();

/*defining struct for */
typedef struct mystruct
{
	void *data_ptr;
	Printfunc print;
	Addfunc add;
	Cleanup cleanup;	
} cell;

/*init functions for cells in the array*/
int InitIntCell		(cell *arr_cell, int num);
int InitFloatCell	(cell *arr_cell, float num);
int InitStringCell	(cell *arr_cell, const char *str);

/*print function*/
void PrintInt	(cell *arr_cell);
void PrintFloat	(cell *arr_cell);
void PrintString(cell *arr_cell);

/*add function*/
int AddInt		(cell *arr_cell, int num);
int AddFloat	(cell *arr_cell, int num);
int AddString	(cell *arr_cell, int num);

/*cleanup functions for mallocs*/
int DoNothing		(cell *arr_cell);
int CleanupString	(cell *arr_cell);

/*BL funcs*/
void InitArray(cell *arr);
void PrintArray(cell *arr);
void AddArray(cell *arr, int int_to_add);
void CleanArray(cell *arr);

/*---------------------------------------------------------------------------*/

int main()
{
	cell arr[AMOUNT_OF_ELEMENTS];
	int int_to_add = INT_TO_ADD;
		
	InitArray(arr);
	PrintArray(arr);
	AddArray(arr, int_to_add);
	PrintArray(arr);
	CleanArray(arr);	

	return 0;
}





/*---------------------------------------------------------------------------*/
/*	initializes struct cell with "INT":
				_____________________________
				|							|
				|	num						|	-	data_ptr
				|___________________________|
				|							|
				|	print func pointer		|	-	print
				|___________________________|
				|							|
				|	AddInt func pointer		|	-	add
				|___________________________|

*/
int InitIntCell(cell *arr_cell, int num)
{
	assert(NULL != arr_cell);
	
	*(int *)&arr_cell->data_ptr = num;
	arr_cell->print = PrintInt;
	arr_cell->add = AddInt;
	arr_cell->cleanup = DoNothing;
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	initializes struct cell with "FLOAT":
	using malloc - Float type not compatible with pointer casting
				_____________________________
				|							|
				|	float					|	-	data_ptr
				|___________________________|
				|							|
				|	print func pointer		|	-	print
				|___________________________|
				|							|
				|	AddFloat func pointer	|	-	add
				|___________________________|
*/


int InitFloatCell(cell *arr_cell, float num)
{
	assert(NULL != arr_cell);
	
	*(float *)&arr_cell->data_ptr = num;
	arr_cell->print = PrintFloat;
	arr_cell->add = AddFloat;
	arr_cell->cleanup = DoNothing;
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	initializes struct cell with "STRING":
	using malloc 
				_____________________________
				|							|
				|	pointer to the string	|	-	data_ptr
				|___________________________|
				|							|
				|	print func pointer		|	-	print
				|___________________________|
				|							|
				|	AddString func pointer	|	-	add
				|___________________________|
*/
int InitStringCell(cell *arr_cell, const char *str)
{
	char *s_ptr = NULL;
		
	assert(NULL != arr_cell);
	assert(NULL != str);
	
	s_ptr = (char *)malloc((sizeof(char) * strlen(str)) + NULL_CHAR_SIZE);	
	if(NULL == s_ptr)
	{
		return 0;
	}
	
	strncpy(s_ptr, str, (strlen(str) + NULL_CHAR_SIZE));
	
	arr_cell->data_ptr = (void *)s_ptr;
	arr_cell->print = PrintString;
	arr_cell->add = AddString;
	arr_cell->cleanup = CleanupString;
		
	return 1;
}


/*---------------------------------------------------------------------------*/
/*	Adds an int to the Data recieved	*/
int AddInt(cell *arr_cell, int num)
{
	assert(NULL != arr_cell);
	
	*(int *)&arr_cell->data_ptr += num;	

	return 1;
}


/*---------------------------------------------------------------------------*/
/*	Adds a float to the Data recieved	*/
int AddFloat(cell *arr_cell, int num)
{
	assert(0 != arr_cell);
	
	*(float *)&arr_cell->data_ptr += num;	
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	Adds a string to the Data recieved	*/
int AddString(cell *arr_cell, int num)
{
	int temp_num = num;
	size_t chars_in_int = 0;
	size_t alloc_chars = 0;
	char *s_ptr = NULL;
	
	assert(NULL != arr_cell);
	
	/*counting number of chars in int*/
	while(0 != temp_num)
	{
		temp_num /= 10;
		++chars_in_int;
	}	
	
	alloc_chars = (strlen(arr_cell->data_ptr) + chars_in_int + NULL_CHAR_SIZE);
	
	s_ptr = (char *)malloc( alloc_chars);
	if(NULL == s_ptr)
	{
		return 0;
	}
		
	/*on C99 should use snprintf - to limit amount of bytes to 'alloc_chars'*/
	sprintf(s_ptr, "%s%d",(char *)arr_cell->data_ptr,num);
	
	free(arr_cell->data_ptr);
	
	arr_cell->data_ptr = (void *)s_ptr;
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	prints int from data_ptr	*/
void PrintInt(cell *arr_cell)
{		
	printf("\nThe data is: %d\n", *(int *)&arr_cell->data_ptr);
	
	return;
}

/*---------------------------------------------------------------------------*/
/*	prints float from data_ptr	*/
void PrintFloat(cell *arr_cell)
{
	printf("\nThe data is: %f\n", *(float *)&arr_cell->data_ptr);
	
	return;
}

/*---------------------------------------------------------------------------*/
/*	prints string from data_ptr	*/
void PrintString(cell *arr_cell)
{
	printf("\nThe data is: %s\n", (char *)arr_cell->data_ptr);
	
	return;
}


/*---------------------------------------------------------------------------*/
/*	does nothing	*/
int DoNothing(cell *arr_cell)
{
	UNUSED(arr_cell);
	return 1;
}


/*---------------------------------------------------------------------------*/
/*	frees malloc of the string	*/
int CleanupString(cell *arr_cell)
{
	free(arr_cell->data_ptr);
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	initializes array of CELLs*/
void InitArray(cell *arr)
{	
	assert(NULL != arr);
	
	InitIntCell(&arr[0], 123);
	InitIntCell(&arr[1], 89745648);
	
	InitFloatCell(&arr[2], 123.58f);
	InitFloatCell(&arr[3], 0.00054f);
	
	InitStringCell(&arr[4], "Serg");
	
	return;	
}


/*---------------------------------------------------------------------------*/
/*	prints data in array of CELLs*/
void PrintArray(cell *arr)
{
	size_t c = 0;

	assert(NULL != arr);
	
	while(AMOUNT_OF_ELEMENTS > c)
	{
		arr[c].print(&arr[c]);
		++c;
	}
	
	return;
}



/*---------------------------------------------------------------------------*/
/*	adds int to array of CELLs*/
void AddArray(cell *arr, int i)
{
	size_t c = 0;

	assert(NULL != arr);
	
	while(AMOUNT_OF_ELEMENTS > c)
	{
		arr[c].add(&arr[c].data_ptr, i);
		++c;
	}
	
	return;
}

/*---------------------------------------------------------------------------*/
/*	frees all memory allocated to array of CELLs*/
void CleanArray(cell *arr)
{
	size_t c = 0;

	assert(NULL != arr);
	
	while(AMOUNT_OF_ELEMENTS > c)
	{
		arr[c].cleanup(&arr[c]);
		++c;
	}
	
	return;
}

