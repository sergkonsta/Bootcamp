#include <stdio.h>
#include <stdlib.h>

/*Functions for LUT*/
void Func1(){system("stty icanon echo"); exit(0);}
void Func2(){printf("A is pressed \n");}
void Func3(){printf("T is pressed \n");}


/*----------------------------------------------------------------------*/

void LUT()
{
	/*initialize array for pointers with NULL */
	void (*LutArr[256])(void) = {NULL};
	
	/*initializing pointers with functions addresses*/
	void(*p1)(void) = &Func1;
	void(*p2)(void) = &Func2;
	void(*p3)(void) = &Func3;
		
	/*Decimal Values of A / T / ESC */
	LutArr[27] = p1;
	LutArr[65] = p2;
	LutArr[84] = p3;
	
	/*disables echo, erase, kill, werase, and rprnt special characters*/
	system("stty -icanon -echo");
	
	/*waits for char and calls for a func in LutArr*/	
	while(1)
	{
		LutArr[getchar()]();
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

