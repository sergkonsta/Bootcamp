
#include "ping_pong.h"

int main()
{
	char *argv[] = {'\0'};

	argv[0] = "ex2.out";
	argv[1] = "./";	
	argv[2] = '\0';
	
	ForkAndExec();
	
	/*PingPongWithFork();*/
	
	return 0;
}
