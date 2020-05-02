/*************************************************
*  			 pqueue functions tests	 			 *
**************************************************/

/*tests by alon yaskil*/

#include <stdio.h>
#include <assert.h>

#include "pqueue.h"

int Compare(const void *data1, const void *data2); 
int AddInt(void *data, void *param);
int IsMatch(const void *data, const void *param);


typedef struct priority
{
	int num;
	int prior;
} data_t;


int main(void)
{
	pq_t *que = NULL;
	int x[] = {1, 4, 7, 8, 13, 15};
	int not_in_x = 20;
	int x_after_erase[] = {1, 4, 8, 13, 15};
	size_t i = 0;
	size_t errors = 0;
	data_t d1 = {15, 1};
	data_t d2 = {13, 2};
	data_t d3 = {8, 3};
	data_t d4 = {7, 4};
	data_t d5 = {4, 5};
	data_t d6 = {1, 6};

/*********** create **********************/
	que = PQCreate(Compare);
	if (PQSize(que) != 0)
	{
		printf("line %d- error size after create\n", __LINE__);
		++errors;
	}
	if (!PQIsEmpty(que))
	{
		printf("line %d- error que is not empty after create\n", __LINE__);
		++errors;
	}


/*********** enq, deq, peek **************/
	PQEnq(que, &d3);
	PQEnq(que, &d2);
	PQEnq(que, &d4);
	PQEnq(que, &d1);
	PQEnq(que, &d6);
	PQEnq(que, &d5);

	while (!PQIsEmpty(que))
	{
		if ((int)(((data_t *)PQPeek(que))->num) != x[i])
		{
			printf("line %d- error wrong data in element number %ld after enq\n", __LINE__, i + 1);
			++errors;
		}

		PQDeq(que);
		++i;
	}

	PQEnq(que, &d3);
	PQEnq(que, &d2);
	PQEnq(que, &d4);

	PQClear(que);
	if (PQSize(que) != 0)
	{
		printf("line %d- error size after clear\n", __LINE__);
		++errors;
	}
	if (!PQIsEmpty(que))
	{
		printf("line %d- error que is not empty after clear\n", __LINE__);
		++errors;
	}

/*********** erase ***********************/
	PQEnq(que, &d3);
	PQEnq(que, &d2);
	PQEnq(que, &d4);
	PQEnq(que, &d1);
	PQEnq(que, &d6);
	PQEnq(que, &d5);
	
	PQErase(que, IsMatch, &(d4.num));

	i = 0;
	while (!PQIsEmpty(que))
	{
		if ((int)(((data_t *)PQPeek(que))->num) != x_after_erase[i])
		{
			printf("line %d- error wrong data in element number %ld after erase\n", __LINE__, i + 1);
			++errors;
		}

		PQDeq(que);
		++i;
	}

	if (PQErase(que, IsMatch, &not_in_x))
	{
		printf("line %d- error not found erase\n", __LINE__);
		++errors;
	}
/*********** destroy *********************/
	PQDestroy(que);


	if (0 == errors)
	{
		puts("all test OK!!");
	}
	else
	{
		printf("number of errors - %ld\n", errors);
	}


	return 0;
}



/*----------------------------------------------------------------------------*/
/*								HELPERS										  */
/*----------------------------------------------------------------------------*/



int Compare(const void *data1, const void *data2)
{
	const data_t *d1 = data1;
	const data_t *d2 = data2;

	assert(data1);
	assert(data2);

	return ((int)d2->prior - (int)d1->prior);
}

int IsMatch(const void *data, const void *param)
{
	const data_t *da = data;
	const data_t *pa = param;

	assert(NULL != data && NULL != param);

	return ((int)da->num == (int)pa->num);
}

int AddInt(void *data, void *param)
{
	assert(NULL != data && NULL != param);

	*(int *)data += *(int *)param;

	return 0;
}

