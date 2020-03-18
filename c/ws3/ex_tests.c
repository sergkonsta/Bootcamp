#include <unistd.h>  		/*for **__environ*/

#include "ex.h"

int main()
{
	PrintEnvLow(__environ);
	
	return 0;
}
