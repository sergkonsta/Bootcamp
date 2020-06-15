/*************************************************
*  			 pqueue functions tests	 			 *
**************************************************/

/*tests by alon yaskil*/

#include <stdio.h>
#include <assert.h>

#include "heap_pq.h"

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
	heap_pq_t *que = NULL;
	int x[] = {15, 13, 8, 7, 4, 1};
	int not_in_x = 20;
	int x_after_erase[] = {15, 13, 8, 4, 1};
	size_t i = 0;
	size_t errors = 0;
	data_t d1 = {15, 1};
	data_t d2 = {13, 2};
	data_t d3 = {8, 3};
	data_t d4 = {7, 4};
	data_t d5 = {4, 5};
	data_t d6 = {1, 6};

/*********** create **********************/
	que = HPQCreate(Compare);
	if (HPQSize(que) != 0)
	{
		printf("line %d- error size after create\n", __LINE__);
		++errors;
	}
	if (!HPQIsEmpty(que))
	{
		printf("line %d- error que is not empty after create\n", __LINE__);
		++errors;
	}


/*********** enq, deq, peek **************/
	HPQEnq(que, &d3);
	HPQEnq(que, &d2);
	HPQEnq(que, &d4);
	HPQEnq(que, &d1);
	HPQEnq(que, &d6);
	HPQEnq(que, &d5);

	while (!HPQIsEmpty(que))
	{
		if ((int)(((data_t *)HPQPeek(que))->num) != x[i])
		{
			printf("line %d- error wrong data in element number %ld after enq\n", __LINE__, i + 1);
			++errors;
		}

		HPQDeq(que);
		++i;
	}

	HPQEnq(que, &d3);
	HPQEnq(que, &d2);
	HPQEnq(que, &d4);

	HPQClear(que);
	if (HPQSize(que) != 0)
	{
		printf("line %d- error size after clear\n", __LINE__);
		++errors;
	}
	if (!HPQIsEmpty(que))
	{
		printf("line %d- error que is not empty after clear\n", __LINE__);
		++errors;
	}

/*********** erase ***********************/
	HPQEnq(que, &d3);
	HPQEnq(que, &d2);
	HPQEnq(que, &d4);
	HPQEnq(que, &d1);
	HPQEnq(que, &d6);
	HPQEnq(que, &d5);
	
	HPQErase(que, IsMatch, &(d4.num));

	i = 0;
	while (!HPQIsEmpty(que))
	{
		if ((int)(((data_t *)HPQPeek(que))->num) != x_after_erase[i])
		{
			printf("line %d- error wrong data in element number %ld after erase\n", __LINE__, i + 1);
			++errors;
		}

		HPQDeq(que);
		++i;
	}

	if (HPQErase(que, IsMatch, &not_in_x))
	{
		printf("line %d- error not found erase\n", __LINE__);
		++errors;
	}
/*********** destroy *********************/
	HPQDestroy(que);


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

