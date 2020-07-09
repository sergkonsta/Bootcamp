#define _XOPEN_SOURCE (600)

#include <stdio.h>	/*for test printf!!!!!!!!!!!!!!!!!!!!!!*/

#include <signal.h>		/*kill, getpid*/
#include <sys/types.h>	/*kill*/
#include <unistd.h>		/*getpid*/
#include <stdlib.h>		/*malloc*/
#include <signal.h>		/*sig_atomic_t*/

#include "wd_utils.h"

static int SchedStopWrapper(void *param);
static int SendRepeatSig(void *params);

struct comm_s
{
	sched_t *my_sched;
	const char *other_side_path;
	sem_t *shared_sem;
	char **new_argv;
	size_t interval;
	size_t num_of_checks;
	pid_t pid;
	pid_t other_side_pid;
};

sig_atomic_t g_stop = 0;
sig_atomic_t g_do_not_revive = 0;
sig_atomic_t g_failed_checks = 0;

comm_t *SetupCommunication(const char *other_side_path,	sem_t *shared_sem, 
							char **new_argv, 
							size_t interval, size_t num_of_checks, 
							pid_t pid, pid_t other_side_pid)
{
	comm_t *info = (comm_t *)malloc(sizeof(comm_t));
	if (NULL == info)
	{
		return NULL;
	}
	
	info->my_sched = SchedCreate();
	if (NULL == info->my_sched)
	{
		free(info);
		return NULL;
	}
	
	info->other_side_path = other_side_path;
	info->shared_sem = shared_sem;
	info->new_argv = new_argv;
	info->interval = interval;
	info->num_of_checks = num_of_checks;
	info->pid = pid;
	info->other_side_pid = other_side_pid;
		
	/*add routine task*/
	SchedAddTask(info->my_sched, SendRepeatSig, (void *)info, interval);
	
	return info;
}




void StartCommunication(comm_t *info)
{
	SchedRun(info->my_sched);
	
	return;
}




void ShutDownCommunication(comm_t *info)
{
	/*other side my_sched already dead, confirm kill*/
	kill(SIGSTOP, info->other_side_pid);
	
	/*g_stop my my_sched*/
	SchedAddTask(info->my_sched, SchedStopWrapper, ((void *)(info->my_sched)), 0);
	
	/*destroy my_sched*/
	free(info);
	
	return;
}

static int SchedStopWrapper(void *param)
{
	
	SchedStop((sched_t *)param);
	
	return 0;
}



static int SendRepeatSig(void *params)
{
	pid_t pid = 0;
	comm_t *info = (comm_t *)params;
	
printf("pid %d signals to 		pid %d     failed checks: %d\n\n", info->pid, info->other_side_pid, g_failed_checks);
	
	
	kill(info->other_side_pid, SIGUSR1);

	if (g_stop)
	{
		return 0;
	}

	if (g_do_not_revive)
	{
		kill(info->other_side_pid, SIGUSR2);
	}
	
	if (!g_do_not_revive && (size_t)g_failed_checks > info->num_of_checks)
	{
		printf("revive \n");
		g_failed_checks = 0;

		pid = fork();

		if (pid)
		{
			info->other_side_pid = pid;
			if (sem_wait(info->shared_sem))
			{
				printf("failed wait task\n");
			}
		}
		
		else
		{
			if (-1 == execv(info->other_side_path, info->new_argv))
			{
				printf("failed exec\n");
				return 0;
			}
		}
	}

	++g_failed_checks;
	
	return 1;
}





























