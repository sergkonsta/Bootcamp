
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      01.04.2020               **
**  Reviewer:  Amir						**
**  Status:    SENT						**
*****************************************/		

/*--------------------------------------------------------------------------*/
/* 									Header 									*/	
/*--------------------------------------------------------------------------*/

#include <stddef.h>		/*for size_t*/
#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/
#include <assert.h>		/*for assert*/
#include <string.h>		/*for original memset*/

#define UNUSED(x) (void)(x)

/*Little endian macro*/
#define LITTLE_ENDIAN_CHECK			unsigned int i = 1; \
									*(char *)&i == 0 ? \
									printf("big endian"); : \
									printf("little endian");
	
/*space ascii value in dec*/
#define SPACE_ASCII (32)

/*letters from A-Z*/
#define NUMBER_OF_LETTERS (26)

/*MACROS for the tests*/
#define ARRAY_SIZES (20)
#define SIZE_OF_NULL_TERM (1)

#define INT_FOR_ITOA (1288)
#define BASE_FOR_ITOA (36)

#define STR_FOR_ATOI ("  AGF123")
#define BASE_FOR_ATOI (23)

/*struct for ThreeArrays()*/
typedef struct cell
{
	char in_arr1;
	char in_arr2;
	char in_arr3;

} cell;

/*Test Function declarations*/
int TestIntToString(int i, unsigned int base);
int TestStringToInt(const char *str, unsigned int base);

/*exercise functions*/
char *IntToString(int num, char *str, unsigned int base);
int StringToInt(const char *str, unsigned int base);
void ThreeArrays(char *a1, char *a2, char *a3);
void LittleEndian();

/*Helper funcs*/
int Power(int x, int y);
void StrRev(char *str);

static char decimal_base_arr[36] = {
				'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
				'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
				'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
				'U', 'V', 'W', 'X', 'Y', 'Z'}; 
				
static int base_arr[92] = {
				0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
				0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
				0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  
				0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 
				0,	0,	0,	0,	0,	0,	0,	0,	0,	1, 
				2,	3,	4,	5,	6,	7,	8,	9,	0,	0, 
				0,	0,	0,	0,	0,	10,	11,	12,	13,	14, 
				15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
				25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
				35,	36};

/*array of structs for ThreeArrays*/
static cell letter[92] ={
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0}
};
				
/*--------------------------------------------------------------------------*/
/* 									Main 									*/	
/*--------------------------------------------------------------------------*/




int main()
{	
	int i_1 = INT_FOR_ITOA;
	char *str = STR_FOR_ATOI;
	
	unsigned int base_1 = BASE_FOR_ITOA;
	unsigned int base_2 = BASE_FOR_ATOI;
	
	/*arrays for Tree_Arrays()*/
	char a1[ARRAY_SIZES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
							'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'};
	
	char a2[ARRAY_SIZES] = {'A', 'X', 'C', 'D', 'X', 'F', 'G', 'X', 'I', 'J',
							'K', 'L', 'X', 'N', 'O', 'X', 'Q', 'R', 'X', 'T'};
	
	char a3[ARRAY_SIZES] = {'A', 'X', 'C', 'D', 'E', 'F', 'G', 'X', 'I', 'J',
							'X', 'L', 'M', 'N', 'X', 'X', 'Q', 'X', 'S', 'T'};
		
	/*start tests*/
	
	LittleEndian();
	
	printf("Starting tests, errors will be printed below.\n\n");
		
	TestIntToString(i_1,base_1);
	
	TestStringToInt(str, base_2);
	
	ThreeArrays(a1, a2, a3);
	
	printf("All done,\nIf no errors were printed, you're good.\n\n");
		
	return 1;
}

/*--------------------------------------------------------------------------*/
/* 								 FUNCTIONS									*/	
/*--------------------------------------------------------------------------*/

/*Little Endian check*/

void LittleEndian()  
{ 
	unsigned int i = 1; 
	
	char *c = (char *)&i;
    
	if (0 != *c)     
	{
		printf("\n\nsystem is Little endian.\n\n"); 
	}

	else
	{
		printf("\n\nsystem is Big endian.\n\n"); 
	}

   	return; 
} 

/*--------------------------------------------------------------------------*/
/*	only works for uppercase arrays.
	array sizes are the same and given in MACRO - ARRAY_SIZES*/
	
void ThreeArrays(char *a1, char *a2, char *a3)
{
	size_t counter = 0;
	size_t char_counter = (int)'A';
	
	assert(NULL != a1);
	assert(NULL != a2);
	assert(NULL != a3);
	
	/*document a1 in struct array*/
	while(ARRAY_SIZES > counter)
	{
		letter[(int)a1[counter]].in_arr1 = '1';
		++counter;
	}
	
	/*document a2 in struct array*/
	counter = 0;
	
	while(ARRAY_SIZES > counter)
	{
		letter[(int)a2[counter]].in_arr2 = '1';
		++counter;
	}
	
	/*document a3 in struct array*/	
	counter = 0;
	
	while(ARRAY_SIZES > counter)
	{
		letter[(int)a3[counter]].in_arr3 = '1';
		++counter;
	}
	
	/*print needed letters*/
	printf("\nThe letters that appear in both a1 & a2 but not in a3 are:\n\n");

	counter = 0;
	char_counter = (int)'A';
	
	while(NUMBER_OF_LETTERS > counter)
	{
		if( '1' == letter[(int)char_counter].in_arr1 &&
			'1' == letter[(int)char_counter].in_arr2 && 
			0 == letter[(int)char_counter].in_arr3)
		{
			printf("%c, ",(char)char_counter);
		}
		
		++char_counter;
		++counter;
	}
	
	printf("\n\n");
	
	return;
}

/*--------------------------------------------------------------------------*/
/* Int to string
perform long division to achieve base conversion
i should be positive
*/
char *IntToString(int i, char *str, unsigned int base)
{
	char *tmp = str;

	assert(0 < i);
	assert(NULL != str);
	
	while(0 != i)
	{
		*tmp = decimal_base_arr[(i % base)];
		++tmp;
		i /= base;
	}	
	++tmp;
	*tmp = '\0';
	
	StrRev(str);
	
	return str;	
}

/*--------------------------------------------------------------------------*/
/* string to int algorithm:

-recieve a str and a base
-check its length
-for every char in the string from end to head 
	-> get decimal value from static array
	-> multiply by base multiplier (base)^(base_counter)
	-> add to result	
*/

int StringToInt(const char *str, unsigned int base)
{
	int result = 0;
	size_t c = 0;
	int base_counter = 0;
	
	assert(NULL != str);
	
	/*space case*/
	while(SPACE_ASCII == *str)
	{
		++str;
	}
	
	/*go to end of str*/
	while('\0' != *(str))
	{
		++str;
		++c;
	}
	--str; 
		
	while(0 != c)
	{		
		result += Power(base,base_counter) * base_arr[(int)*str];
		++base_counter;
		--str;	
		--c; 
	}
	
	return result;	
}


/*--------------------------------------------------------------------------*/
/*raises X in the power of Y*/

int Power(int x, int y)
{	 
    int temp = 0; 
    
    if(y == 0) 
    {
    	return 1; 
    }
    
    temp = Power(x, y/2); 
    
    if (y % 2 == 0) 
    {
    	return temp * temp; 
    }
    
    else
    {
    	return x * temp * temp; 
    }
}


/*--------------------------------------------------------------------------*/
/*Reverses str*/

void StrRev(char *str)
{
	size_t length = strlen(str);
	size_t c = 0;
	char tmp = '\0';
	
	char *end = str + length - 1;
		
	while(c < (length / 2))
	{
		tmp = *end;
		*end = *str;
		*str = tmp;
		
		++c;
		++str;
		--end;	
	}
}
	
/*--------------------------------------------------------------------------*/
/* 							TEST FUNCTIONS									*/	
/*--------------------------------------------------------------------------*/

int TestIntToString(int i, unsigned int base)
{
	size_t digits = 0;
	char *str = NULL;
	int tmp = i;
	
	while(0 != tmp)
	{
		tmp /= 10;
		++digits;
	} 

	str = (char *)malloc((digits + SIZE_OF_NULL_TERM) * sizeof(char));
	if(NULL == str)
	{
		return 0;
	}
	
	str = IntToString(i, str, base);

	printf("\nInt To String test:\n");
	printf("%d in base %u is: %s\n\n",i,base, str);

	free(str);
	
	return 1;
}

/*--------------------------------------------------------------------------*/

int TestStringToInt(const char *str, unsigned int base)
{	
	assert(NULL != str);
	
	printf("\nString To Int test:\n");
	printf("%s in base %u is: %d\n\n",str,base, StringToInt(str, base));
		
	return 1;
}

	
				
