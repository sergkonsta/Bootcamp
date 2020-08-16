/*
Project:	task
Developer:	Sergey Konstantinovsky
Date:		29/04/2020
*/

#include <assert.h>		/*for assert*/
#include <stdlib.h>		/*for malloc*/
#include <time.h>		/*for time*/

#include "task.h"

struct task
{
	ilrd_uid_t uid;
	size_t time_to_run; 			/*shows next time to run*/
	size_t interval_in_sec; 		
	int (*act_func)(void *param); 	/*returns if task should repeat or not*/
	void *param;					/*param for act_fun*/
};

/*----------------------------------------------------------------------------*/
/*
function: 	creates a task according to task struct 
success:	pointer to task
fail:		NULL
*/
task_t *TaskCreate(	int (*act_func)(void *param), void *param, 
					size_t interval_in_sec)
{
	task_t *new_task = NULL;
	
	assert(NULL != act_func);
	
	new_task = (task_t *)malloc( sizeof(task_t) );
	if(NULL == new_task)
	{
		return NULL;
	}
	
	new_task->uid = UIDCreate();
	/*forgot to check returned UID not to be BAD_UID*/
	
	new_task->interval_in_sec = interval_in_sec;
	new_task->act_func = act_func;
	new_task->param = param;
	new_task->time_to_run = time(NULL) + interval_in_sec;
	
	return (new_task);
}



/*----------------------------------------------------------------------------*/
/*
function:	runs act_func
success:	1 for repeat / 0 for don't repeat
fail:		--- 
*/
int TaskRun(task_t *task)
{
	assert(NULL != task);
	assert(NULL != task->act_func);
	
	return (task->act_func(task->param));
}


/*----------------------------------------------------------------------------*/
/*
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
function:	frees task.
success:	---
fail:		---
*/
void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->act_func = NULL;
	task->param = NULL;
	
	free(task);
	task = NULL;
}


/*----------------------------------------------------------------------------*/
/*
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
function: 	checks if task has the same UID as 'uid'
success: 	1 - is a match / 0 - no match
fail:		---
*/
int TaskIsMatch(const void *task, const void *uid)
{
	assert(NULL != task);
	
	return UIDIsSame(TaskGetId(task), *(ilrd_uid_t *)uid);
}


