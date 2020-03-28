
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      25.03.2020               **
**  Reviewer:  Roy						**
**  Status:    SENT						**
*****************************************/
#include <stdio.h>	/*for printf*/
#include <math.h>	/*for pow()*/
#include <stdbool.h>/*for bool*/

#include "bitwise.h"

int main()
{
	int c = 111;
	int d = 22;
	unsigned int x = 7;
	unsigned int y = 5;

	unsigned char b = 0x18;
	const unsigned int arr[5] = {2149582848, 3758096384, 0, 4294967295, 11111};
	
	float fnum = 0;
	
	
	/*print float*/
	fnum = 1.23;

	PrintFloatBits(fnum);
		
			
	/*ClosestNumber check*/
	/*while(z < 161)
	{
		printf("\nclosest number to %d, divisable by 16: %d",z,ClosestNumber(z));
		++z;
	}*/
	
	/*SwapBits check*/
	printf("\nfrom 0xA7 to: %x\n",SwapBits(0xA7));
	
	/*TwoAndSix check*/
	if(true == TwoAndSix(0x33))
	{
		printf("\ndigits 2 and 6 both on\n");
	}
	
	else
	{
		printf("\ndigits 2 and 6 aren't both on\n");
	}
	
	/*TwoOrSix check*/
	if(true == TwoOrSix(0x20))
	{
		printf("\ndigits 2 or 6 is on\n");
	}
	
	else
	{
		printf("\ndigits 2 and 6 both zero\n");
	}
	
	/*ByteMirror check*/
	printf("\nthe char is %x",b);
	printf("\nthe flipped char is %x",ByteMirror(b));
	printf("\nthe flipped with loop char is %x",ByteMirrorLoop(b));
	
	/*ThreeBits check*/
	ThreeBits(arr, 5);
	
	/*Pow2 ckeck*/
	printf("\nThe result of Pow2 with x: %d, y: %d, is: %ld\n",x,y,Pow2(x,y));
	
	/*IsPow check*/
	x = 1;
		
	printf("\nThe result of IsPow with x: %d, is: %d\n",x,IsPow(x));
	printf("\nThe result of IsPow with x: %d, is: %d\n",x,IsPowNoLoop(x));
	
	/*AddOne check*/
	x = 214748364;
	
	if(AddOne((int)x) != x+1)
	{
		printf("\nWRONG on: %d\n",x);
	}
	else 
	{
		printf("\nsuccess with 214748364\n");
	}
		
	/*Swap Var check*/
	printf("\nc & d before swap: %d, %d\n",c,d);
	SwapVar(&c,&d);
	printf("\nc & d after swap: %d, %d\n",c,d);
	SwapVar(&c,&d);
	
	/*CountSetBitsLoop check*/
	printf("\nThe amount of set bits in %d is: %ld \n",c,CountSetBitsLoop(c));
	/*CountSetBitsLoop check*/
	printf("\nThe amount of set bits in %d is: %ld \n",c,CountSetBits(c));	
	
	
	return 0;
}





