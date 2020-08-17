#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include <stddef.h>		/*size_t*/

/* watchdog uses SIGUSER1 SIGUSER2 */
/*must run client with excutable path as first CLI arg second arg if exists, will be moved to the right*/

typedef struct watchdog_s watchdog_t;

/* The function starts the WatchDog. Return: NULL if FAIL. */
watchdog_t *WDMMI(const char *client_path, size_t interval, size_t num_of_checks, char **client_process_argv);

/* The fuction closes the given process. */
int WDDNR(watchdog_t *watchdog);

#endif 

