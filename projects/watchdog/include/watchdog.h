#ifndef __OL87_WATCHDOG_H__
#define __OL87_WATCHDOG_H__

#include <stddef.h>		/*size_t*/


typedef struct watchdog_s watchdog_t;

/* watchdog uses SIGUSER1 SIGUSER2 */
/* The function starts the WatchDog.
	Return: NULL if FAIL. */
	
/*must run client with excutable path as first CLI arg
second ard if exists, will be moved to the right*/
watchdog_t *WDMMI(const char *client_path, size_t interval, size_t num_of_checks, char **client_process_argv);

/* The fuction closes the given process. */
int WDDNR(watchdog_t *watchdog);


#endif /* __OL87_WATCHDOG_H__*/

/*	MMI sets thread. - MMI need to check if an instance of wathcdog process is already up in env of client process.
		(check in env)
	If no watchdog process is up:
	thread function call fork and exec to set watchdog process.
	MMI function stay active to wait for watchdog OK signal.
	MMI function return OK status to client.
	MMI create semaphor - wait 
	When semaphor was posted : sched RUN
	If Watchdog is already up - sched Run immidietly. 
	comunication between thread and watchdog VIA signals.
	every interval (heartbeat) 
		watchdog process runs scheduler and reschedule a task to send is_alive signal to client process
		watchdog process need to check is_alive(SIG_USR1) signal from client process. 
		watchdog is_alive - signal handler - restart timer_variable.
			if timer was not restarted num_of_checks times -
			task return non-repeat val to sched.
			watchdog kill client process watchdog
			watchdog re-run client_process again.  
		watchdog process need to check if DNR has sent END_MMI signal.
	
	thread - symetry with watchdog process (same function!) 
	
	DNR (send SIGUSR2 to watchdog process and also send watchdog_thread signal to end it); 

	wd_test.c -> include wd.h
	wd.c -> wd.o -> include wd.h with MMI() DNR()
        
     
	wd_utils.c -> wd_utils.o -> wd_utils.h include functions for wathcdog exec

	watchdog_exe.c -> include wd_utils.h (with main of watchdog (include wd.utils)

	watchdog_lib.so is shared library with both wd.o and wd_utils.o

*/
