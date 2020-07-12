/*
Project:	Watchdog
Developer:	Sergey Konstantinovsky
Date:		10/07/2020
*/

#ifndef __OL87_WD_UTILS_H__
#define __OL87_WD_UTILS_H__

#include <semaphore.h>

#include "sched.h"

#define ENV_NAME "SERG-WD"

#define UNUSED(X) (void)(X)

typedef struct watchdog_s
{
	char **other_side_argv;
	sched_t *my_sched;
	const char *other_side_path;
	size_t interval;
	size_t num_of_checks;
	pid_t other_side_pid;
	pthread_t thread_2_join;
} wd_t;

typedef enum 
{
	RUN,
	SEND,
	STOP
} sched_state_t;


extern sig_atomic_t g_sched_op;
extern sem_t *wd_sem; 

/*sets up scheduler*/
int SetupCommunication(wd_t *wd);

/*starts sched*/
int StartCommunication(wd_t *wd);
int TrackCommunication(wd_t *wd);

#endif /* __OL87_WD_UTILS_H__*/


