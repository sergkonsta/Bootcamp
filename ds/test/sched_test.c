
#include <stdio.h>


#include "sched.h"

typedef struct help help_struct_t;

struct help
{
	void *param_for_act_fun;
	time_t start_time;
	int is_repeat;
};

int PrintForActfunc(void *int_to_print);

int main()
{
	sched_t *sched = SchedCreate();	
	
	/*init UIDs for logging tasks*/
	ilrd_uid_t uid_1 = {0};
	
	/*initialize param */
	help_struct_t param_to_send = {0};
	
	printf("\n\n");
	/*------------------------------------------------------------------------*/
	if( 1 != SchedIsEmpty(sched) ) /*should be empty*/
	{
		printf("\nproblem in line: %d",__LINE__);
	}

	/*uid 	=	sched, act_func, (void *)param[struct], delta(t)-when to run*/
	uid_1 = SchedAddTask(sched, PrintForActfunc, (void *)&param_to_send, 5);
	
	if( 1 == SchedIsEmpty(sched) ) /*should not be empty*/
	{
		printf("\nproblem in line: %d",__LINE__);
	}
	
	
	/*remove task using uid*/
	SchedRemove(sched, uid_1);

	uid_1 = SchedAddTask(sched, PrintForActfunc, (void *)&param_to_send, 5);
	
	SchedClear(sched);








	/*------------------------------------------------------------------------*/
	printf("\n\n");
	SchedDestroy(sched);	
	return 1;
}

int PrintForActfunc(void *int_to_print)
{
	int x = (int)int_to_print;
	
	printf("\n%d,",x);
	
	return (1);
}








