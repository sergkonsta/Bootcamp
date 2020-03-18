#include <stddef.h>		/*for size_t*/
#include <stdbool.h>	/*for bool*/
#include <stdlib.h>		/*for malloc*/
#include <stdio.h>		/*for printf*/



size_t HungerGames(size_t num_of_knights)
{
	bool *start = (bool *)malloc(num of knights * sizeof(bool));
	bool *start_copy = start;
	bool last_knight = false;
	
	size_t amount_alive = num_of_knights;
	size_t counter = 0;
	size_t result = 0;
	
	/*As long there is more than 1 knight alive*/
	while(1 < amount_alive)
	{
		/*what knight starts the rotation*/
		counter = 0;
		
		/*until a full circle is made (full pass of the array)*/
		while(counter < num_of_knights)
		{
			/*if last knight is alive and the current knight is alive*/
			if((true == last_knight) && (true == start[counter]))
			{
				start[counter] = false; 
				last_knight = false;
				--amount_alive;			
			}
			
			else
			{
				last_knight = true;
				
				/*save last survivor place in array*/
				if(2 == amount_alive)
				{
					result = counter;
				}
			}
			
			++counter;
		}
	}
	
	free(start_copy);
	
	return result;
	
}

int main()
{
	printf("\n The lasts survivors place is: %ld", HungerGames(100));
}

