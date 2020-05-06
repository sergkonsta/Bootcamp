




/*		tests from Yael 		*/



#include <stdio.h>

#include "sched.h"
#include "task.h"

#define ERROR (printf("Error in line %d\n", __LINE__), ++errors)

typedef struct to_remove
{
	ilrd_uid_t uid;
	sched_t *sched;
}to_remove_t;

/* Action functions */
static int AddNumOneToData(void *data);
static int Size(void *data);
static int RemoveTask(void *data);
static int PrintLeftToRun(void *data);
static int StopSched(void *data);

int main ()
{
	/**********task***********/
	task_t *task = NULL;
	
	ilrd_uid_t uid = {0, 0, 0};
	
	int number = 3;
	
	/**********sched***********/
	size_t errors = 0;
	
	int num1 = 5;
	int num2 = 100;
	
	int left_to_run = 20;
	
	to_remove_t remove_data = {0};
	
	sched_t *sched = SchedCreate();
	
	ilrd_uid_t uid1 = {0};

	/**********task tests***********/
	task = TaskCreate(AddNumOneToData, &number, 1);

	if(TaskGetNextRunTime(task) != time(NULL) + 1)
	{
		ERROR;
	}
		
	TaskRun(task);
	
	TaskUpdateNextRun(task);
	
	if(TaskGetNextRunTime(task) != time(NULL) + 1)
	{
		ERROR;
	}

	uid = TaskGetId(task);

	if (TaskIsMatch(task, &uid) != 1)
	{
		ERROR;
	}
	
	TaskDestroy(task);
	
	/**********sched tests***********/
	if(!SchedIsEmpty(sched))
	{
		ERROR;
	}
	
	SchedAddTask(sched, AddNumOneToData, &num1, 10);
	SchedAddTask(sched, AddNumOneToData, &num2, 10);
	
	/*Size-task runs until StopSched acts*/
	uid1 = SchedAddTask(sched, Size, sched, 5);
	SchedAddTask(sched, PrintLeftToRun, &left_to_run, 5);
	
	SchedAddTask(sched, StopSched, sched, 20);
	
	remove_data.sched = sched;
	remove_data.uid = uid1;
	/*removing task (size)*/
	SchedAddTask(sched, RemoveTask, &remove_data, 12);
	
	if(SchedSize(sched) != 6)
	{
		ERROR;
	}
	
	SchedRun(sched);
		
	SchedDestroy(sched);
	
	return 0;
}


static int AddNumOneToData(void *data)
{
	printf("AddNumOneToData() start running...\n");
	printf("Before: data = %d\n", *(int*)data);
	*(int*)data += 1;
	printf("After: data = %d\n", *(int*)data);
	printf("-----------------------------\n");
	
	return 0;
}

static int Size(void *data)
{
	printf("Size() start running...\n");
	printf("%lu\n", SchedSize((sched_t*)data));
	printf("-----------------------------\n");
	
	return 1;
}

static int RemoveTask(void *data)
{
	to_remove_t *remove_data = (to_remove_t*)data;
	printf("RemoveTask() start running...\n");
	SchedRemove(remove_data->sched, remove_data->uid);
	printf("-----------------------------\n");
	
	return 0;
}

static int PrintLeftToRun(void *data)
{
	*(int*)data -= 1;
	printf("PrintLeftToRun() start running...\n");
	printf("%d times left to run!\n", *(int*)data);
	printf("-----------------------------\n");
	
	return (*(int*)data != 0);
}

static int StopSched(void *data)
{
	printf("StopSched() start running...\n");
	SchedStop((sched_t*)data);
	printf("-----------------------------\n");
	
	return 0;
}
