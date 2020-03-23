#include <stdlib.h> /*	for: system("stty icanon echo"), print */
#include <stdio.h>	/*	for printf */

#define LUT_SIZE 256
#define ESC 27

/*-----------------------Functions for LUT------------------------------*/

/*Exit function*/
void ExitFunc()
{
	system("stty icanon echo"); 
	exit(0);
}

/*Prints A*/
void PrintA()
{
	printf("A is pressed \n");
}

/*Prints T*/
void PrintT()
{
	printf("T is pressed \n");
}

/*Does nothing*/
void NonFunc()
{
	return;
}


/*----------------------------------------------------------------------*/

void LUT()
{
	size_t i = 0;
				
	/*initialize array for pointers with NULL */
	void (*lut_arr[LUT_SIZE])(void) = {NULL};

		
	/*fill array with poiters to function which does nothing*/
	while(LUT_SIZE > i)
	{
		lut_arr[i] = &NonFunc;
		++i;
	}
		
	/*store the pointers in the array*/
	/*Decimal Values of A / T / ESC */
	lut_arr[ESC] = &ExitFunc;
	lut_arr['A'] = &PrintA;
	lut_arr['T'] = &PrintT;
	
	/*disables echo, erase, kill, werase, and rprnt special characters*/
	system("stty -icanon -echo");
	
	/*waits for char and calls for a func in LutArr*/	
	while(1)
	{
		lut_arr[getchar()]();
	}
}

/*----------------------------------------------------------------------*/

void SwitchCase()
{
	/*disables echo, erase, kill, werase, and rprnt special characters*/
	system("stty -icanon -echo");
	
	while(1)
	{
		switch (getchar())
		{
			case 'A':
			printf("A is pressed\n");
			break;
			
			case 'T':
			printf("T is pressed\n");
			break;
			
			case 0x1B:
			system("stty icanon echo");
			return;
			
		}
	}
}

/*----------------------------------------------------------------------*/

void IfElse()
{
	
	char ch = 0;
	
	/*disables echo, erase, kill, werase, and rprnt special characters*/
	system("stty -icanon -echo");
		
	while(1)
	{
		ch = getchar();
		
		if (ch == 0x1B)
		{
			system("stty icanon echo");
			return;
		}
		
		else if (ch == 'T')
		{
			printf("T is pressed \n");
		}
		
		else if (ch == 'A')
		{
			printf("A is pressed \n");
		}
	}
}



/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      22.03.2020               **
**  Reviewer:  Hannah					**
**  Status:    Approved					**
*****************************************/

/*----------------------------------------------------------------------*/


int main ()
{

	LUT();

	return 0;
	
}

