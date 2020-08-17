/*
Project:	Watchdog
Developer:	Sergey Konstantinovsky
Date:		10/07/2020
*/

#define _POSIX_C_SOURCE 200809L  /*sigaction requirement*/

#include <signal.h>		/*kill, getpid*/
#include <sys/types.h>	/*kill*/
#include <unistd.h>		/*getpid*/
#include <stdlib.h>		/*malloc*/
#include <signal.h>		/*sig_atomic_t*/
#include <semaphore.h>	/*sem_open, sem_wait*/
#include <fcntl.h>		/*O_* ocnstants*/
#include <sys/stat.h>	/*mode constants*/
#include <assert.h>		/*assert*/

#include "wd_utils.h"

static int PingAndCheckTask(void *params);
static void ResetSig(int sig);
static void StopSchedSig(int sig);

sig_atomic_t g_sched_op = RUN;
sig_atomic_t g_failed_checks = 0;

sem_t *wd_sem = NULL;

int SetupCommunication(wd_t *wd)
{
	/*setup signals*/
	struct sigaction sig1 = {0};
	struct sigaction sig2 = {0};

	assert(wd);

	sig1.sa_handler = ResetSig;
	if (sigaction(SIGUSR1, &sig1, NULL))
	{
		return -1;
	}
	
	sig2.sa_handler = StopSchedSig;
	if (sigaction(SIGUSR2, &sig2, NULL))
	{
		return -1;
	}
	
	/*setup semaphore*/
	wd_sem = sem_open(ENV_NAME, O_CREAT, 0666, 0);
	if (SEM_FAILED == wd_sem)
	{
		return -1;
	}
	
	wd->my_sched = SchedCreate();
	if (NULL == wd->my_sched)
	{
		return -1;
	}
	
	/*add routine task*/
	SchedAddTask(wd->my_sched, PingAndCheckTask, wd, wd->interval);
	
	return 0;
}


int ReviveOtherProc(wd_t *wd)
{
	assert(wd);
	
	wd->other_side_pid = fork();

	if (wd->other_side_pid < 0)
	{
		return -1;
	}
	
	if (0 == wd->other_side_pid)
	{
		execvp(wd->other_side_path, wd->other_side_argv);

		return -1;
	}

	return 0;
}

int StartCommunication(wd_t *wd)
{
	assert(wd);
	
	SchedRun(wd->my_sched);

	while (RUN == g_sched_op)
	{
		/*confirm kill*/
		kill(wd->other_side_pid, SIGKILL);

		if (ReviveOtherProc(wd))
		{
			return -1;
		}
		
		g_failed_checks = 0;

		sem_wait(wd_sem);
		SchedRun(wd->my_sched);
	}
	
	SchedDestroy(wd->my_sched);

	return 0;
}

/*----------------------------------------------------------------------------*/
/*task for the schedulers*/
static int PingAndCheckTask(void *param)
{
	wd_t *wd = (wd_t *)param;

	assert(param);

	if (STOP == g_sched_op)
	{	
		SchedStop(wd->my_sched);
		return 0;
	}
	
	if (RUN == g_sched_op)
	{
		++g_failed_checks;    
		
		if((unsigned int)g_failed_checks >= wd->num_of_checks)
		{	
			SchedStop(wd->my_sched);
		}
	}
	
	kill(wd->other_side_pid, SIGUSR1);

	return 1; 
}

/*----------------------------------------------------------------------------*/
/*increments counter of amounts of signals recieved from wd*/
static void ResetSig(int sig)
{
	UNUSED(sig);
	g_failed_checks = 0;
}

static void StopSchedSig(int sig)
{
	UNUSED(sig);
	g_sched_op = STOP;
}



