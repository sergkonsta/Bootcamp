
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      30.03.2020               **
**  Reviewer:  Irina					**
**  Status:    Sent						**
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
int InitIntCell(CELL *arr_cell, long num);
int InitFloatCell(CELL *arr_cell, float num);
int InitStringCell(CELL *arr_cell, const char *str);

/*print function*/
void PrintInt(void *data);
void PrintFloat(void *data);
void PrintString(void *data);

/*add function*/
int AddInt(CELL *arr_cell, int num);
int AddFloat(CELL *arr_cell, int num);
/*with malloc*/
int AddString(CELL *arr_cell, int num);

/*cleanup functions for mallocs*/
int DoNothing(void *data);
int CleanupString(void *data);


/*---------------------------------------------------------------------------*/

int main()
{
	CELL test1;
	CELL test2;
	CELL test3;
	
	int x = 5;
	
	InitIntCell(&test1, 123);
	test1.print(test1.data_ptr);
	AddInt(&test1, x);
	test1.print(test1.data_ptr);
	test1.cleanup(test1.data_ptr);
	
	InitFloatCell(&test2, 12.59);
	test2.print(test2.data_ptr);
	AddInt(&test2, x);
	test2.print(test2.data_ptr);
	test2.cleanup(test2.data_ptr);
	
	InitStringCell(&test3, "Serg");
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
int InitIntCell(CELL *arr_cell, long int num)
{
	assert(0 != arr_cell);
	
	arr_cell->data_ptr = (void *)num;
	arr_cell->print = PrintInt;
	arr_cell->add = AddInt;
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


int InitFloatCell(CELL *arr_cell, float num)
{
	long int *ip = (long int *)&num;
	
	arr_cell->data_ptr = (void *)(long int *)*ip;
	arr_cell->print = PrintFloat;
	arr_cell->add = AddFloat;
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
	/*arr_cell->add = AddFloat;*/
	arr_cell->cleanup = CleanupString;
	
	/*checks that the values match*/
	assert(0 == strcmp(str, (const char *)arr_cell->data_ptr));
	
	return 1;
}


/*---------------------------------------------------------------------------*/
/*	Adds an int to the Data recieved

*/
int AddInt(CELL *arr_cell, int num)
{
	arr_cell->data_ptr = (void *)((long int)arr_cell->data_ptr + (long int)num);

	return 1;
}


/*---------------------------------------------------------------------------*/
/*	Adds a float to the Data recieved

*/
int AddFloat(CELL *arr_cell, int num)
{
	float fnum = *(float *)&arr_cell->data_ptr + (float)num;
	printf("%f",fnum);
	
	
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
