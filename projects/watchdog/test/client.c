#include <stdio.h>

#include <unistd.h>	/*sleep*/

#include "watchdog.h"

#define UNUSED(X) (void)(X)


int main(int argc, char *argv[])
{
    size_t sleeper = 0;
    
    watchdog_t *watchdog = NULL;

    UNUSED(argc);

    watchdog = WDMMI(argv[0], 2, 5, argv);
	printf("\nmain client continues\n");	
    
    
    while (sleeper < 5)
	{
		sleep(1);
		printf("tick..\n");
		++sleeper;
	}
    
    
    WDDNR(watchdog);
	printf("\nmain client ended\n");	
    return 0;
}
