#include <stdio.h>
#include <stdlib.h>


void Func1(){	system("stty icanon echo");	exit(0);}
void Func2(){	printf("A is pressed \n");}
void Func3(){	printf("T is pressed \n");}


/*----------------------------------------------------------------------*/

void LUT()
{
	/*initialize array of pointers with NULL */
	void (*LutArr[256])(void) = {NULL};
	
	void(*p1)(void) = Func1;
	void(*p2)(void) = Func2;
	void(*p3)(void) = Func3;
	
	system("stty -icanon -echo");
	
	/*Decimal Values of A / T / ESC */
	LutArr[27] = p1;
	LutArr[65] = p2;
	LutArr[84] = p3;
	

	
	while(1)
	{
		LutArr[getchar()]();
	}
}

/*----------------------------------------------------------------------*/

void SwitchCase()
{
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

