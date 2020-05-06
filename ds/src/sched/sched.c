
/*****************************************
**  Developer: Sergey Konstantinovsky   **
**  Date:      03.05.2020               **
**  Reviewer:  ???						**
**  Status:    ?????					**
*****************************************/	
#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/
#include <time.h>		/*for time()*/

#include "sched.h"
#include "pqueue.h"
#include "task.h"

typedef struct help help_struct_t;

struct help
{
	void *param_for_act_fun;
	time_t start_time;
	int is_repeat;
};

struct sched
{
	pq_t *pq;
	int to_stop;			/*flag to stop event loop */
	task_t *current_task; 	/*is NULL if no task is running*/
};

int Compare(const void *data1, const void *data2);
int IsMatchForRemove(const void *task, const void *uid);


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	creates a scheduler 
Success:	pointer to sched
fail:		NULL
*/
sched_t *SchedCreate(void)
{
	sched_t *new_sched = (sched_t *)malloc( sizeof(sched_t) );
	if(NULL == new_sched)
	{
		return (NULL);
	}
	
	new_sched->pq = PQCreate(Compare);
	if(NULL == new_sched->pq)
	{
		free(new_sched);
		return (NULL);
	}
	
	/*don't stop event loop*/
	new_sched->to_stop = 0;
	
	/*no task yet*/
	new_sched->current_task = NULL;	
	
	return (new_sched);	
}




/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	destroys
Success:	pointer to sched
fail:		NULL
*/
void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	/*clears all tasks*/
	SchedClear(sched);
	
	PQDestroy(sched->pq);

	free(sched);
	
	return;
}



/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	returns size of sched 
			(during runtime if there is a task running 
			will be +1 for current task)
Success:	size_t
fail:		---
*/
size_t SchedSize(const sched_t *sched)
{	
	assert(NULL != sched);
	
	/*adds 1 to size if there is a current task running*/
	return (PQSize(sched->pq) + (size_t)(NULL != sched->current_task));
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	checks if sched is empty
Success:	1 for empty or 0 for not empty
fail:		---
*/
int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	return (PQIsEmpty(sched->pq) && (NULL == sched->current_task));
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	clears all tasks
Success:	---
fail:		---
*/
void SchedClear(sched_t *sched)
{
	assert(NULL != sched);
	
	while(1 != SchedIsEmpty(sched))
	{
		SchedRemove(sched, TaskGetId( (task_t *)PQPeek( sched->pq) ));
	}
	
	return;
}



/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	removes a specific task, UID must be correct
Success:	---
fail:		---
*/
void SchedRemove(sched_t *sched, ilrd_uid_t uid)
{
	const void *uid_to_remove = (const void *)&uid;
	
	assert(NULL != sched);
		
	free( PQErase(sched->pq, IsMatchForRemove, uid_to_remove) );
	
	return;
}


/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	Adds new task to scheduler
Success:	UID of added task
fail:		---
*/
/* void *param - how many times task should repeat
	interval - time to start (when calling add func- time 0) + interval
	act_func - what the task should do (print or whate...)
	act_func returns int as status if task should be repeated/ if not should be repeated/ success*/
	
ilrd_uid_t SchedAddTask(sched_t *sched, 
						int(*act_func)(void *param),
						void *param, 
						size_t interval_in_sec)
{
	task_t *new_task = TaskCreate( 	act_func,
									param, 
									interval_in_sec );
	PQEnq(sched->pq, new_task);
	
	return ( TaskGetId(new_task) );
}




/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	runs scheduler
Success:	---
fail:		---
*/
int SchedRun(sched_t *sched)
{
	/*save run start time*/
	time_t start_time = time(NULL);

	int return_status = 0;
		
	/*event loop*/
	while((1 != sched->to_stop) && (1 != SchedIsEmpty(sched)))
	{		
		/*begin first task*/
		sched->current_task = (task_t *)PQDeq(sched->pq);	
			
		/*if its time to run*/
		if (	(size_t)(time(NULL) - start_time) == 
				TaskGetNextRunTime(sched->current_task) )
		{
			/*if task should repeat - put it back in queue*/
			if (1 == TaskRun(sched->current_task) )
			{
				PQEnq(sched->pq, sched->current_task); /*with same time interval*/
			}
			
			/*task finished*/
			sched->current_task = NULL;	
		}		
	}	
	
	return (return_status);
}



/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	turns on to_stop
Success:	---
fail:		---
*/

void SchedStop(sched_t *sched)
{
	assert (NULL != sched);
	
	sched->to_stop = 1;
	
	return;
}


/*----------------------------------------------------------------------------*/
/*								HELPERS FUNCS								  */
/*----------------------------------------------------------------------------*/
int Compare(const void *data1, const void *data2)
{
	/*need to compare [ input time + time interval ] in order to sort in pqueue*/
	return (1);
}


int IsMatchForRemove(const void *task, const void *uid)
{
	task_t *task_to_check = (task_t *)task;
	ilrd_uid_t *uid_to_remove = (ilrd_uid_t *)uid;	
	
	return ( TaskIsMatch(task_to_check, *uid_to_remove) );
}
















