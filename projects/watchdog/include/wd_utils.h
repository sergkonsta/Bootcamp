#ifndef __OL87_WD_UTILS_H__
#define __OL87_WD_UTILS_H__

#include <semaphore.h>

#include "sched.h"

#define SEM_NAME "watchdog_started_sigs_sem"
#define WD_FLAG "WATCHDOG_IS_RUNNING"
#define INT_ENV "INTERVAL_BETWEEN_WD_CHECKS"
#define NUM_ENV "NUM_OF_WD_CHECKS"
#define PATH_ENV "PATH_OF_CLIENT"
#define PATH_ENV_WD "PATH_OF_WATCHDOG"

typedef struct comm_s comm_t;

struct watchdog_s
{
	comm_t *my_info;
	const char *my_path;
	char **my_argv;
	size_t interval;
	size_t num_of_checks;
	pid_t pid;
	pthread_t *thread_2_join;
};

/*sets up scheduler*/
comm_t *SetupCommunication(const char *other_side_path, sem_t *shared_sem, 
							char **new_argv, 
							size_t interval, size_t num_of_checks, 
							pid_t pid, pid_t other_side_pid);

/*starts sched*/
void StartCommunication(comm_t *info);

void ShutDownCommunication(comm_t *info);

#endif /* __OL87_WD_UTILS_H__*/


