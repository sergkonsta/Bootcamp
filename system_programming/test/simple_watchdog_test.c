
#include "simple_watchdog.h"

int main ()
{
	char *argv[] = {'\0'};

	argv[0] = "InfiniteLoop.out";
	argv[1] = "./";	
	argv[2] = '\0';
	SimpleWatchdog(argv);
	
			
	/*run case divide by zero - excpect exit status of 1*/
	argv[0] = "DivideByZero.out";
	argv[1] = "./";
	argv[2] = '\0';
	SimpleWatchdog(argv);
	
	/*run case terminated by SIGTERM - excpect ???*/
	argv[0] = "TerminatedBySignal.out";
	argv[1] = "./";	
	argv[2] = '\0';
	SimpleWatchdog(argv);
	
	
	return 0;
}
