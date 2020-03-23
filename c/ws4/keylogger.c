#include <stdlib.h> /*	for: system("stty icanon echo"), print */
#include <stdio.h>	/*	for printf */


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
	
	/*initializing pointers with functions addresses*/
	void(*p1)(void) = &ExitFunc;
	void(*p2)(void) = &PrintA;
	void(*p3)(void) = &PrintT;
	void(*p_non)(void) = &NonFunc;
		
	/*initialize array for pointers with NULL */
	void (*lut_arr[256])(void) = {NULL};

		
	/*fill array with poiters to function which does nothing*/
	while(256 > i)
	{
		lut_arr[i] = p_non;
		++i;
	}
		
	/*store the pointers in the array*/
	/*Decimal Values of A / T / ESC */
	lut_arr[27] = p1;
	lut_arr[65] = p2;
	lut_arr[84] = p3;
	
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
	/*disables echo, erase, kill, werase, and rprnt special characters*/
	system("stty -icanon -echo");
		
	while(1)
	{
		if (getchar() == 0x1B)
		{
			system("stty icanon echo");
			return;
		}
		
		else if (getchar() == 'T')
		{
			printf("T is pressed \n");
		}
		
		else if (getchar() == 'A')
		{
			printf("A is pressed \n");
		}
	}
}



/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      22.03.2020               **
**  Reviewer:  Hannah					**
**  Status:    Sent						**
*****************************************/

/*----------------------------------------------------------------------*/


int main ()
{

	LUT();

	return 0;
	
}

