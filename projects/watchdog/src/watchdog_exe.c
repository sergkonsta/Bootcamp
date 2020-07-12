/*
Project:	Watchdog
Developer:	Sergey Konstantinovsky
Date:		10/07/2020
*/
#include <signal.h>		/*sig_atomic_t*/
#include <stdlib.h>		/*atoi*/
#include <semaphore.h>	/*sem_post*/
#include <sys/types.h>	/*pid_t*/
#include <unistd.h>		/*pid_t*/

#include "wd_utils.h"

extern sig_atomic_t g_sched_op;
extern sig_atomic_t g_failed_checks;

int main(int argc, char *argv[])
{
	/*init wd struct*/	
	wd_t *wd = (wd_t *)malloc(sizeof(wd_t));
	if (NULL == wd)
	{
		return -1;
	}
	
	UNUSED(argc);
	
	/*set up sched on wd side*/
	wd->other_side_path = argv[2];
	wd->other_side_argv = argv + 2;
	wd->interval = atoi(argv[0]);
	wd->num_of_checks = atoi(argv[1]);
	wd->other_side_pid = getppid();
	
	if (SetupCommunication(wd))
	{
		return -1;
	}
	
	sem_post(wd_sem);

	/*start sched on wd side*/
	StartCommunication(wd);

	/*sched is ended, tell client to stop*/
	kill(wd->other_side_pid, SIGUSR2);
	
	free(wd);

	return 0;	
}


