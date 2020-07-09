#include <stdio.h>

#include "watchdog.h"



int main(int argc, char *argv[])
{
	
	watchdog_t *watchdog = NULL;
	
	watchdog = WDMMI(argv[0], 5, 3, argv);
	
	WDDNR(watchdog);
	
	return 0;
}
