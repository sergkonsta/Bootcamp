#include <unistd.h>  		/*for **__environ*/
#include <stdlib.h>			/*for free()	*/

#include "ex.h"

int main()
{
	PrintEnvLow(__environ);

	return 0;
}
