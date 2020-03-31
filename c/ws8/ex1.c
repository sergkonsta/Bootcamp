
/*####### STILL HAS MEMMORY LOSS ##########*/

/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      31.03.2020               **
**  Reviewer:  Irina					**
**  Status:    Sent						**
*****************************************/

#include <stdio.h>	/*for printf*/
#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for strlen, strcpy, strcmp*/

/*amount of elements in array*/
#define AMOUNT_OF_ELEMENTS (5)
#define NULL_CHAR_SIZE (1)
#define UNUSED(data) (void)(data)

/*defining function pointers for struct*/
typedef void (*printfunc)();
typedef int (*addfunc)();
typedef int (*cleanup)();

/*defining struct for */
typedef struct _mystruct
{
	void *data_ptr;
	printfunc print;
	addfunc add;
	cleanup cleanup;
	
} CELL;

/*init functions for cells in the array*/
int InitIntCell		(CELL *arr_cell, int num);
int InitFloatCell	(CELL *arr_cell, float num);
int InitStringCell	(CELL *arr_cell, const char *str);

/*print function*/
void PrintInt	(void *data);
void PrintFloat	(void *data);
void PrintString(void *data);

/*add function*/
int AddInt		(CELL *arr_cell, int num);
int AddFloat	(CELL *arr_cell, int num);
int AddString	(CELL *arr_cell, int num);

/*cleanup functions for mallocs*/
int DoNothing		(void *data);
int CleanupString	(void *data);

/*BL funcs*/
void InitArray(CELL *arr);
void PrintArray(CELL *arr);
void AddArray(CELL *arr, int int_to_add);
void CleanArray(CELL *arr);

/*---------------------------------------------------------------------------*/

int main()
{
	CELL arr[AMOUNT_OF_ELEMENTS];
	
	int int_to_add = 999;
	
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
int InitIntCell(CELL *arr_cell, int num)
{
	assert(0 != arr_cell);
	
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


int InitFloatCell(CELL *arr_cell, float num)
{
	assert(0 != arr_cell);
	
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
int InitStringCell(CELL *arr_cell, const char *str)
{
	char *s_ptr = NULL;
		
	assert(0 != arr_cell);
	assert(0 != str);
	
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
int AddInt(CELL *arr_cell, int num)
{
	assert(0 != arr_cell);
	
	*(int *)&arr_cell->data_ptr += num;	

	return 1;
}


/*---------------------------------------------------------------------------*/
/*	Adds a float to the Data recieved	*/
int AddFloat(CELL *arr_cell, int num)
{
	assert(0 != arr_cell);
	
	*(float *)&arr_cell->data_ptr += num;	
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	Adds a string to the Data recieved	*/
int AddString(CELL *arr_cell, int num)
{
	int temp_num = num;
	
	size_t chars_in_int = 1;
	size_t realloc_chars = 0;
	
	char *s_ptr = NULL;
	
	assert(0 != arr_cell);
	
	/*counting number of chars in int*/
	while(0 != temp_num)
	{
		++chars_in_int;
		temp_num /= 10;
	}	
	
	realloc_chars = (strlen(arr_cell->data_ptr) + chars_in_int + NULL_CHAR_SIZE);
	
	s_ptr = (char *)realloc(arr_cell->data_ptr, sizeof(char) * realloc_chars);
	
	/*on C99 should use snprintf - to limit amount of bytes to 'realloc_chars'*/
	sprintf(s_ptr, "%s%d",s_ptr,num);
	
	arr_cell->data_ptr = (void *)s_ptr;
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	prints int from data_ptr	*/
void PrintInt(void *data)
{		
	printf("\nThe data is: %ld\n", (long int)data);
	
	return;
}

/*---------------------------------------------------------------------------*/
/*	prints float from data_ptr	*/
void PrintFloat(void *data)
{
	printf("\nThe data is: %f\n", *(float *)&data);
	
	return;
}

/*---------------------------------------------------------------------------*/
/*	prints string from data_ptr	*/
void PrintString(void *data)
{
	printf("\nThe data is: %s\n", (char *)data);
	
	return;
}


/*---------------------------------------------------------------------------*/
/*	does nothing	*/
int DoNothing(void *data)
{
	UNUSED(data);
	return 1;
}


/*---------------------------------------------------------------------------*/
/*	frees malloc of the string	*/
int CleanupString(void *data)
{
	free(data);
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*	initializes array of CELLs*/
void InitArray(CELL *arr)
{	
	assert(0 != arr);
	
	InitIntCell(&arr[0], 123);
	InitIntCell(&arr[1], 89745648);
	
	InitFloatCell(&arr[2], 123.58f);
	InitFloatCell(&arr[3], 0.00054f);
	
	InitStringCell(&arr[4], "This Is a      Test String");
	
	return;	
}


/*---------------------------------------------------------------------------*/
/*	prints data in array of CELLs*/
void PrintArray(CELL *arr)
{
	size_t c = 0;

	assert(0 != arr);
	
	while(AMOUNT_OF_ELEMENTS > c)
	{
		arr[c].print(arr[c].data_ptr);
		++c;
	}
	
	return;
}



/*---------------------------------------------------------------------------*/
/*	adds int to array of CELLs*/
void AddArray(CELL *arr, int i)
{
	size_t c = 0;

	assert(0 != arr);
	
	while(AMOUNT_OF_ELEMENTS > c)
	{
		arr[c].add(&arr[c].data_ptr, i);
		++c;
	}
	
	return;
}

/*---------------------------------------------------------------------------*/
/*	frees all memory allocated to array of CELLs*/
void CleanArray(CELL *arr)
{
	size_t c = 0;

	assert(0 != arr);
	
	while(AMOUNT_OF_ELEMENTS > c)
	{
		arr[c].cleanup(&arr[c].data_ptr);
		++c;
	}
	
	return;
}

