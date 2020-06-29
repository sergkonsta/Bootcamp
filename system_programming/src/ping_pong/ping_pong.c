/*
Developer: Sergey Konstantinovsky
Date:      28.06.2020
Reviewer:  
*/
#include <stdlib.h>		/*for exit*/
#include <sys/types.h>	/*for waitpid & fork*/
#include <unistd.h>		/*for fork, pause*/
#include <stdio.h>		/*for printf*/
#include <signal.h>		/*for signal*/

#include "ping_pong.h"

#define UNUSED(X) (void)(X)

static void UserSig(int sig);

static sig_atomic_t to_print = 0;



/*----------------------------------------------------------------------------*/
int ForkAndExec(char *argv[])
{
	pid_t child_id = 0;

	/*Establish the signal handler*/
	struct sigaction usr_action = {0};
	
	usr_action.sa_handler = UserSig;
	
	sigaction(SIGUSR1, &usr_action, NULL);
	
	child_id = fork();
	
	/*parent case: fork failed case*/
	if (child_id == -1)
	{
		exit(0);
	} 
	
	while (1)
	{
		/*parent proc case: he recieved the child's child_id*/
		if (child_id > 0)
		{
			sleep(2);
			
			kill(child_id, SIGUSR1);
			
			pause();
			
			if (1 == to_print)
			{
				printf("\n signal recieved from child");
			
				to_print = 0;
			}
			
			sleep(1);
			
		}
		
		/*child proc case: (child_id == 0)*/
		else 
		{
			/*case successfull exit*/
			execv("./ex2.out", NULL);
		}
	}
	
	return 0;
}




/*----------------------------------------------------------------------------*/
int PingPongWithFork()
{
	pid_t child_id = 0;

	/*Establish the signal handler*/
	struct sigaction usr_action = {0};
	
	usr_action.sa_handler = UserSig;
	
	sigaction(SIGUSR1, &usr_action, NULL);
	sigaction(SIGUSR2, &usr_action, NULL);
	
	child_id = fork();
	
	/*parent case: fork failed case*/
	if (child_id == -1)
	{
		exit(0);
	} 
	
	while (1)
	{
		/*parent proc case: he recieved the child's child_id*/
		if (child_id > 0)
		{
			kill(child_id, SIGUSR1);
			
			pause();
			
			if (1 == to_print)
			{
				printf("\n signal recieved from child");
			
				to_print = 0;
			}
			
			sleep(1);
			
		}
		
		/*child proc case: (child_id == 0)*/
		else 
		{
			kill(getppid(), SIGUSR2);
			
			pause();
			
			if (1 == to_print)
			{
				printf("\n\t\t\t\tsignal recieved from parent");
			
				to_print = 0;
			}
			
			sleep(1);
		}
	}
	
	return 0;
}


/*sig action that prints for SIGUSR1 & 2*/
static void UserSig(int sig)
{
	UNUSED(sig);
	
	to_print = 1;
}

