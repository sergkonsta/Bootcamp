#define _XOPEN_SOURCE (600)

#include <stdio.h>	/*for test printf!!!!!!!!!!!!!!!!!!!!!!*/
#include <string.h>	/*for test strcmp!!!*/
#include <unistd.h>	/*sleep test!!!*/

#include <signal.h>		/*sigaction, sig_atomic_t*/
#include <stdlib.h>		/* setenv, atoi*/
#include <semaphore.h>	/*sem_open, sem_wait*/
#include <fcntl.h>		/*O_* ocnstants*/


#include "wd_utils.h"

#define UNUSED(X) (void)(X)

typedef struct watchdog_s watchdog_t;

static void Usr1Handler(int signum);
static void Usr2Handler(int signum);

extern sig_atomic_t g_stop;
extern sig_atomic_t g_do_not_revive;
extern sig_atomic_t g_failed_checks;

int main(int argc, char *argv[])
{
	watchdog_t *watchdog = NULL;
	
	struct sigaction sig1;
	struct sigaction sig2;
	
	/*Establish the signal handler*/
	sig1.sa_handler = Usr1Handler;
	sig2.sa_handler = Usr2Handler;
	
	if(sigfillset(&sig1.sa_mask) || sigfillset(&sig2.sa_mask) 
	|| sigdelset(&sig1.sa_mask, SIGUSR1) || sigdelset(&sig2.sa_mask, SIGUSR2)
	|| sigdelset(&sig1.sa_mask, SIGTERM) || sigdelset(&sig2.sa_mask, SIGTERM) 
	|| sigaction(SIGUSR1, &sig1, NULL) || sigaction(SIGUSR2, &sig2, NULL))
	{
		printf("failed sig stuff wd \n");
		return -1;
	}
	
	/*init watchdog struct*/	
	watchdog = (watchdog_t *)malloc(sizeof(watchdog_t));
	if (NULL == watchdog)
	{
		return NULL;
	}
	watchdog->my_info = NULL;
	watchdog->my_path = getenv(PATH_ENV);
	watchdog->argv = argv;
	watchdog->interval = (size_t)atoi( getenv(INT_ENV) );
	watchdog->num_of_checks = (size_t)atoi( getenv(NUM_ENV) );
	watchdog->pid = getpid();
	
	WDTask((void *)watchdog);
	
	return 0;
}


int WDTask(void *param)
{
	watchdog_t *watchdog = (watchdog_t *)param;
	sem_t *sem = sem_open(SEM_NAME, 0);
	
	/*set up sched on wd side*/
	watchdog->wd_info = SetupCommunication(getenv(PATH_ENV), sem, watchdog->argv, 
									watchdog->interval, watchdog->num_of_checks, 
									watchdog->pid, getppid();

	sem_post(sem);

	/*start sched on wd side*/
	StartCommunication(info);
	
	/*my comms are up - let client continue*/
	/*sem_post(sem);*/
	sem_unlink(SHAREDSEM);
	free(info);

	printf("finished wd \n");
	return res;
	
}


/*----------------------------------------------------------------------------*/
/*increments counter of amounts of signals recieved from watchdog*/
static void Usr1Handler(int signum)
{
	UNUSED(signum);
	g_failed_checks = 0;
}

static void Usr2Handler(int signum)
{
	UNUSED(signum);
	g_stop = 1;
}
