/*
Developer: Sergey Konstantinovsky
Date:      24.06.2020
Reviewer:  
*/

#include <stdlib.h>		/*for exit*/
#include <sys/types.h>	/*for waitpid & fork*/
#include <sys/wait.h>	/*for waitpid*/
#include <unistd.h>		/*for fork, exe*/
#include <stdio.h>		/*for printf*/
#include <string.h>		/*for strcat*/

#include "simple_watchdog.h"

static void CheckForkReturnStatusImp(int status);
static int SystemImp(char *argv[]);
static int ForkImp(char *argv[]);

int SimpleWatchdog(char *argv[])
{
	/*ForkImp(argv);*/
	
	SystemImp(argv);
	
	return 0;
}





static int SystemImp(char *argv[])
{
	char *abs_path = (char *)malloc(sizeof(char) * (strlen(argv[0]) + strlen(argv[1]) + 1));
	size_t i = 0;
	
	*abs_path = '\0';
	
	strcat(abs_path, argv[1]);
	strcat(abs_path, argv[0]);
	
	while (1)
	{
		system(abs_path);	
	}
	
	free(abs_path);
	return 0;
}





static int ForkImp(char *argv[])
{
	size_t i = 0;
	
	for (;i < 3; ++i)
	{	
		/*dupes current proc*/	
		pid_t pid = fork();

		/*parent case: fork failed case*/
		if (pid == -1)
		{
			exit(0);
		} 
		
		/*parent proc case: he recieved the child's pid*/
		else if (pid > 0)
		{
			int status;
			
			/*parent waits for child to be done*/
			wait(&status);
			
			/*check status for different macros*/
			CheckForkReturnStatusImp(status);
		}
		
		/*child proc case: (pid == 0)*/
		else 
		{
			/*case successfull exit*/
			sleep(1);
			execv(argv[1], argv);

			/*in case execution fails - exit and pass failed status to parent*/
			exit(EXIT_FAILURE);
		}
	}
	
	return 0;
}


static void CheckForkReturnStatusImp(int status)
{
	/*normal termination
 	if true - can employ WEXITSTATUS(status) to check status */
	if (WIFEXITED(status))
	{
		printf("\nexited with normal status of: %d.\n",WEXITSTATUS(status));
	}
	
	/*stopped by signal*/
	else if (WIFSTOPPED(status))
	{
		printf("\nwas terminated by signal number: %d.\n",WSTOPSIG(status));
	}
	
	/*terminated by signal*/
	else if (WIFSIGNALED(status))
	{
		printf("\nwas terminated by signal number: %d.\n",WTERMSIG(status));
		
		if (__WCOREDUMP(status))
		{
			printf("\nCore was dumped.");
		}
	}
}



