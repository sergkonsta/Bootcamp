#include <stdio.h>


#include "sched.h"
#include "watchdog.h"


void FuncWD_UTILS()
{
	sched_t *sched = SchedCreate();

	printf("\nI am writing from wd_utils.c\n");
	

}
