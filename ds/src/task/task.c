
#include <assert.h>		/*for assert*/
#include <stdlib.h>		/*for malloc*/
#include <time.h>

#include "task.h"

struct task
{
	ilrd_uid_t uid;
	size_t time_to_run; 			/*my comment: shows next time to run*/
	size_t interval_in_sec; 		/*first time to run and all after if repeat is on*/
	int (*act_func)(void *param); 	/*returns repeat or not*/
	void *param;					/*param for act_fun*/
};

/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	creates a task according to task struct 
success:	pointer to task
fail:		NULL
*/
task_t *TaskCreate(	int (*act_func)(void *param), void *param, 
					size_t interval_in_sec)
{
	task_t *new_task = {0};
	
	assert(NULL != act_func);
	
	new_task = (task_t *)malloc( sizeof(task_t) );
	if(NULL == new_task)
	{
		return NULL;
	}
	
	new_task->uid = UIDCreate();
	new_task->interval_in_sec = interval_in_sec;
	new_task->act_func = act_func;
	new_task->param = param;
	new_task->time_to_run = time(NULL) + interval_in_sec;
	
	return (new_task);
}



/*----------------------------------------------------------------------------*/
/*
O(1)
function:	runs act_func
success:	1 for repeat / 0 for don't repeat
fail:		--- (can't fail - Tal said)
*/
int TaskRun(task_t *task)
{
	assert(NULL != task);
	
	return (task->act_func(task->param));
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	gets UID of the task
success: 	return UID of the task
fail: 		---	
*/
ilrd_uid_t TaskGetId(const task_t *task)
{
	assert(NULL != task);

	return (task->uid);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	frees task.
success:	---
fail:		---
*/
void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	free(task);	
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function: returns next time to run
success:
fail:
*/
size_t TaskGetNextRunTime (const task_t *task)
{
	assert (NULL != task);
	
	return (task->time_to_run);
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function:	updates next run time according to interval
			
success: 	---
fail:		---
*/
void TaskUpdateNextRun(task_t *task)
{
	assert(NULL != task);
	
	task->time_to_run = time(NULL) + task->interval_in_sec;
}


/*----------------------------------------------------------------------------*/
/*
O(1)
function: 	checks if task has the same UID as 'uid'
success: 	1 - is a match / 0 - no match
fail:		---
*/
int TaskIsMatch(const void *task,const void *uid)
{
	assert(NULL != task);
	
	return UIDIsSame(TaskGetId(task), *(ilrd_uid_t *)uid);
}


