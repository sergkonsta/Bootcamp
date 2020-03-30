
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      30.03.2020               **
**  Reviewer:  ?????					**
**  Status:    ?????					**
*****************************************/

#include <stdio.h>	/*for printf*/
#include <stdlib.h>	/*for malloc*/
#include <assert.h>	/*for assert*/
#include <string.h>	/*for strlen, strcpy, strcmp*/


/*amount of elements in array*/
#define AMOUNT_OF_ELEMENTS (10)
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
int InitIntCell(long num, CELL *arr_cell);
int InitFloatCell(float num, CELL *arr_cell);
/*with Malloc*/
int InitStringCell(const char *str, CELL *arr_cell);

/*print function*/
void PrintInt(void *data);
void PrintFloat(void *data);
void PrintString(void *data);

/*add function*/
int AddInt(int num, void *data);
int AddFloat(int num, void *data);
/*with malloc*/
int AddString(int num, void *data);

/*cleanup functions for mallocs*/
int DoNothing(void *data);
int CleanupString(void *data);


/*---------------------------------------------------------------------------*/

int main()
{
	CELL test1;
	CELL test2;
	CELL test3;
	
	InitIntCell(123, &test1);
	test1.print(test1.data_ptr);
	test1.cleanup(test1.data_ptr);
	
	InitFloatCell(12.59, &test2);
	test2.print(test2.data_ptr);
	test2.cleanup(test2.data_ptr);
	
	InitStringCell("Serg", &test3);
	test3.print(test3.data_ptr);
	test3.cleanup(test3.data_ptr);


	return 0;
}

/*---------------------------------------------------------------------------*/

/*	initializes struct cell with "INT":
				_____________________________
				|							|
				|	casted int to (void *)	|	-	data_ptr
				|___________________________|
				|							|
				|	print func pointer		|	-	print
				|___________________________|
				|							|
				|	AddInt func pointer		|	-	add
				|___________________________|

*/
int InitIntCell(long int num, CELL *arr_cell)
{
	assert(0 != arr_cell);
	
	arr_cell->data_ptr = (void *)num;
	arr_cell->print = PrintInt;
	/*arr_cell->add = AddInt;*/
	arr_cell->cleanup = DoNothing;
	
	/*checks that the values match*/
	assert(num == (long int)arr_cell->data_ptr);
	
	return 1;
}

/*---------------------------------------------------------------------------*/

/*	initializes struct cell with "FLOAT":
	using malloc - Float type not compatible with pointer casting
				_____________________________
				|							|
				|	pointer to the float num|	-	data_ptr
				|___________________________|
				|							|
				|	print func pointer		|	-	print
				|___________________________|
				|							|
				|	AddFloat func pointer	|	-	add
				|___________________________|
*/


int InitFloatCell(float num, CELL *arr_cell)
{
	long int *ip = (long int *)&num;
	
	arr_cell->data_ptr = (void *)(long int *)*ip;
	arr_cell->print = PrintFloat;
	/*arr_cell->add = AddFloat;*/
	arr_cell->cleanup = DoNothing;
	
	/*checks that the values match*/
	assert(num == *((float*)&arr_cell->data_ptr));
	
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
				|	AddFloat func pointer	|	-	add
				|___________________________|
*/
int InitStringCell(const char *str, CELL *arr_cell)
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
	/*arr_cell->add = AddFloat;*/
	arr_cell->cleanup = CleanupString;
	
	/*checks that the values match*/
	assert(0 == strcmp(str, (const char *)arr_cell->data_ptr));
	
	return 1;
}


/*---------------------------------------------------------------------------*/

/*	prints int from data_ptr

*/
void PrintInt(void *data)
{
	printf("\nThe data is: %ld\n", (long int)data);
	
	return;
}

/*---------------------------------------------------------------------------*/

/*	prints float from data_ptr

*/
void PrintFloat(void *data)
{
	printf("\nThe data is: %f\n", *(float *)&data);
	
	return;
}

/*---------------------------------------------------------------------------*/

/*	prints string from data_ptr

*/
void PrintString(void *data)
{
	printf("\nThe data is: %s\n", (char *)data);
	
	return;
}


/*---------------------------------------------------------------------------*/

/*	does nothing

*/
int DoNothing(void *data)
{
	UNUSED(data);
	return 1;
}


/*---------------------------------------------------------------------------*/

/*	frees malloc of the string

*/
int CleanupString(void *data)
{
	free(data);
	
	return 1;
}
