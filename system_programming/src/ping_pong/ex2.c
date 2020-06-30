
#define _XOPEN_SOURCE (600)

#include <sys/types.h>	/*for waitpid & fork*/
#include <unistd.h>		/*for fork, pause*/
#include <stdio.h>		/*for printf*/
#include <signal.h>		/*for signal*/

#define UNUSED(X) (void)(X)

static void UserSig(int sig);

static sig_atomic_t to_print = 0;


/*----------------------------------------------------------------------------*/
int main()
{
	/*Establish the signal handler*/
	struct sigaction usr_action = {0};
	
	pid_t parent_id = getppid();
	
	usr_action.sa_handler = UserSig;
	sigaction(SIGUSR1, &usr_action, NULL);
	
	while (1)
	{
		pause();
		
		kill(parent_id, SIGUSR1);
		
		if (1 == to_print)
		{
			printf("\n signal recieved from parent");
			to_print = 0;
		}
		
		sleep(1);
	}
	
	return 0;
}


/*sig action that prints for SIGUSR1*/
static void UserSig(int sig)
{
	UNUSED(sig);
	
	to_print = 1;
}
