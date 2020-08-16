/*
Project:	Scheduler
Developer:	Sergey Konstantinovsky
Date:		03/05/2020
*/

#include <stdlib.h>		/*for malloc*/
#include <assert.h>		/*for assert*/
#include <time.h>		/*for time()*/
#include <unistd.h>		/*for sleep()*/

#include "sched.h"
#include "heap_pq.h"
#include "task.h"

ilrd_uid_t BAD_UID = {0,0,0};

struct sched
{
	heap_pq_t *pq;
	int to_stop;			/*flag to stop event loop */
	task_t *current_task; 	/*is NULL if no task is running*/
};

int Compare(const void *task_in_pq, const void *time_to_start);

/*----------------------------------------------------------------------------*/
/*
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
	
	new_sched->pq = HPQCreate(Compare);
	if(NULL == new_sched->pq)
	{
		free(new_sched);
		return (NULL);
	}
	
	new_sched->to_stop = 0;
	new_sched->current_task = NULL;	
	
	return (new_sched);	
}




/*----------------------------------------------------------------------------*/
/*
function: 	destroys
Success:	pointer to sched
fail:		NULL
*/
void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	assert(NULL != sched->pq);
	
	/*clears all tasks*/
	SchedClear(sched);
	
	sched->current_task = NULL;
	
	HPQDestroy(sched->pq);

	free(sched);
	sched = NULL;
	
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
	assert(NULL != sched->pq);
	
	/*adds 1 to size if there is a current task running*/
	return (HPQSize(sched->pq) + (size_t)(NULL != sched->current_task));
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
	assert(NULL != sched->pq);
	
	return (HPQIsEmpty(sched->pq) && (NULL == sched->current_task));
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
	assert(NULL != sched->pq);
	
	/*HPQIsEmpty and not SchedIsEmpty - to make sure loop won't be infinite*/
	while (!HPQIsEmpty(sched->pq))
	{
		TaskDestroy(HPQDeq(sched->pq));
	}
	
	return;
}



/*----------------------------------------------------------------------------*/
/*
O(n)
function: 	removes a specific task, UID must be correct
Success:	---
fail:		if HPQErase return NULL, no operation is performed.
*/
void SchedRemove(sched_t *sched, ilrd_uid_t uid)
{	
	assert(NULL != sched);
	
	/*self remove check - current_task might be null*/
	if (NULL == sched->current_task)
	{
		free( HPQErase(sched->pq, TaskIsMatch, &uid ));
	}
	
	else
	{
		if (0 == TaskIsMatch(sched->current_task, &uid))
		{
			free( HPQErase(sched->pq, TaskIsMatch, &uid ));
		}	
	}					
			
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
	task_t *new_task = NULL;
	
	assert(NULL != sched);
	assert(NULL != sched->pq);
	assert(NULL != act_func);
	
	new_task = TaskCreate( 	act_func, param, interval_in_sec );
	if (NULL == new_task)
	{
		return BAD_UID;
	}		

	if (0 !=	HPQEnq(sched->pq, new_task))
	{
		return BAD_UID;
	}
	
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
	size_t time_offset = 0;
	
	assert(NULL != sched);
	assert(NULL != sched->pq);
	
	sched->to_stop = 0;
	
	/*event loop*/
	while ((1 != sched->to_stop) && (1 != SchedIsEmpty(sched)))
	{		
		/*get first task*/
		sched->current_task = (task_t *)HPQDeq(sched->pq);
			/*missing: check that current task is really empty*/	

		/*check when first task should occur*/
		time_offset = TaskGetNextRunTime(sched->current_task) - time(NULL);
		
		/*wait and make sure sleep doesn't wake up early*/
		while (time_offset > 0)
		{
			sleep(time_offset);
			time_offset = TaskGetNextRunTime(sched->current_task) - time(NULL);
		}
		
		/*destroy non-repeating task after it occurs*/
		if (0 == TaskRun(sched->current_task))
		{
			TaskDestroy(sched->current_task);
		}
		
		/*repeating task: put it back in the scheduler*/
		else
		{
			TaskUpdateNextRun(sched->current_task);
			
			/*if enq failed, 
			  keep task in current task so the client can reEnq it*/
			if (0 != HPQEnq(sched->pq, sched->current_task))
			{
				SchedStop(sched);
				
				return -1;
			}
		}	
		
		sched->current_task = NULL;					
	}	
		
	
	return (sched->to_stop);
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
	assert(NULL != sched);
	assert(NULL != sched->pq);
	
	sched->to_stop = 1;
	
	return;
}


/*----------------------------------------------------------------------------*/
/*								HELPERS FUNCS								  */
/*----------------------------------------------------------------------------*/

/* returns 0 for equality*/
int Compare(const void *task_in_pq, const void *time_to_start)
{
	return ( TaskGetNextRunTime((task_t*)task_in_pq) -
			 TaskGetNextRunTime((task_t*)time_to_start));
}















