/*
Developer: Sergey Konstantinovsky
Date:      21.06.2020
Reviewer:  Jenia	
*/

#include <assert.h>	/*for assert*/

#include "bit_array.h"
#include "knights_tour.h"

#define NUM_POSSIBLE_MOVES (8)
#define NUM_OF_COLUMNS (8)
#define NUM_OF_ROWS (8)
#define NUM_OF_SQUARES (NUM_OF_COLUMNS * NUM_OF_ROWS)
#define INVALID_INDEX (NUM_POSSIBLE_MOVES + 1)
#define INVALID_MOVE (NUM_OF_SQUARES + 1)
#define UNUSED(x) (void)(x)

typedef enum status
{
	SUCCESS,
	FAIL
} status_t;


static void InitLUTImp(unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES]);
static status_t TourImp(unsigned char pos, unsigned char *res_path,
	unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES], bit_arr_t step_made);

/*********** heuristic functions ***********/
#ifdef HEURISTIC
static size_t CountValidMovesImp(unsigned char pos, bit_arr_t step_made,
				unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES]);
static size_t NextMinImp(unsigned char pos, bit_arr_t step_made, 
						unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES]); 
static void SwapMovesImp(size_t first, size_t min, unsigned char pos,
				    unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES]);
#endif


/******************** Knights_Tour **************************************/
int KnightsTour(unsigned char init_pos, unsigned char *res_path)
{
	unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES] = {0};

	assert(NULL != res_path);

	InitLUTImp(lut);

	return (int)TourImp(init_pos, res_path, lut, 0);
}



/******************** TourImp ***************************************/
static status_t TourImp(unsigned char pos, unsigned char *res_path,
	unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES], bit_arr_t step_made)
{
	size_t i = 0;
	size_t index_next_min = 0;

	step_made = BArrSetOn(step_made, pos);

	if (0 == BArrCountOff(step_made))
	{
		*res_path = pos;
		return SUCCESS;
	}

/* warnsdorf expansion, move next move with least possibilties to first 
   position of current square list */
#ifdef HEURISTIC
	index_next_min = NextMinImp(pos, step_made, lut);
	if (INVALID_INDEX != index_next_min)
	{
		SwapMovesImp(0, index_next_min, pos, lut);
	}
#else
	UNUSED(index_next_min);
#endif

	/* run over all possibilties */
	while (INVALID_MOVE != lut[pos][i] && i < NUM_POSSIBLE_MOVES)
	{
		/* if next move is first visited */
		if (0 == BArrGetVal(step_made, lut[pos][i]))
		{
			if (SUCCESS == TourImp(lut[pos][i],res_path + 1, lut, step_made))
			{
				*res_path = pos;
				return SUCCESS;
			}
		}

		++i;
	}
	return FAIL;
}

/******************** InitLUTImp ****************************************/
/* init moves LUT, for each position, check all possible moves */
static void InitLUTImp(unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES])
{
	size_t square_num = 0;
	size_t num_of_move = 0;

	for (square_num = 0; square_num < NUM_OF_SQUARES; ++square_num)
	{
		for (num_of_move = 0; num_of_move < NUM_POSSIBLE_MOVES; ++num_of_move)
		{
			lut[square_num][num_of_move] = INVALID_MOVE;
		}
	}

	for (square_num = 0; square_num < NUM_OF_SQUARES; ++square_num)
	{
		num_of_move = 0;

		if (square_num > 16 && square_num % NUM_OF_ROWS > 0)
		{
			lut[square_num][num_of_move] = square_num - 17;
			++num_of_move;
		}
		if (square_num >= 16 && square_num % NUM_OF_ROWS < 7)
		{
			lut[square_num][num_of_move] = square_num - 15;
			++num_of_move;
		}
		if (square_num > 8 && square_num % NUM_OF_ROWS > 1)
		{
			lut[square_num][num_of_move] = square_num - 10;
			++num_of_move;
		}

		if (square_num >= 8 && square_num % NUM_OF_ROWS < 6)
		{
			lut[square_num][num_of_move] = square_num - 6;
			++num_of_move;
		}

		if (square_num < 56 && square_num % NUM_OF_ROWS > 1)
		{
			lut[square_num][num_of_move] = square_num + 6;
			++num_of_move;
		}

		if (square_num < 56 && square_num % NUM_OF_ROWS < 6)
		{
			lut[square_num][num_of_move] = square_num + 10;
			++num_of_move;
		}

		if (square_num < 48 && square_num % NUM_OF_ROWS > 0)
		{
			lut[square_num][num_of_move] = square_num + 15;
			++num_of_move;
		}

		if (square_num < 48 && square_num % NUM_OF_ROWS < 7)
		{
			lut[square_num][num_of_move] = square_num + 17;
			++num_of_move;
		}
	}
}

#ifndef SLOW
/******************** CountValidMovesImp *******************************/
/* check how many moves possible from each position, and not visited yet */
static size_t CountValidMovesImp(unsigned char pos, bit_arr_t step_made,
				unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES])
{
	size_t i = 0;
	size_t counter = 0;

	for (i = 0; INVALID_MOVE != lut[pos][i] && i < NUM_POSSIBLE_MOVES; ++i)
	{
		if (0 == BArrGetVal(step_made, lut[pos][i]))
		{
			++counter;
		}
	}

	return counter;
}

/******************** NextMinImp *********************************/
/* find next move with least possibilties and return its index */
static size_t NextMinImp(unsigned char pos, bit_arr_t step_made, 
						unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES]) 
{
	size_t index_min_possibilities = INVALID_INDEX;
	size_t num_of_min_options = 0;
	size_t num_of_options = 0;
	size_t i = 0;

	for (i = 0; i < NUM_POSSIBLE_MOVES && INVALID_MOVE != lut[pos][i]; ++i)
	{
		if  (0 == BArrGetVal(step_made, lut[pos][i]))
		{
			num_of_options = CountValidMovesImp(lut[pos][i], step_made, lut);

			/* if first possible move , store it */
			if (INVALID_INDEX == index_min_possibilities && 
										(0 < num_of_options))
			{
				num_of_min_options = num_of_options;
				index_min_possibilities = i;
			}
			/* if current possible move have less next moves than previous
			   found store it */
			else if (INVALID_INDEX != index_min_possibilities && 
				(0 < num_of_options) && (num_of_options < num_of_min_options)) 
			{
				num_of_min_options = num_of_options;
				index_min_possibilities = i;
			}
		}
	}

	return index_min_possibilities;
}
/******************** SwapMovesImp *********************************/
static void SwapMovesImp(size_t first, size_t min, unsigned char pos,
				    unsigned char lut[NUM_OF_SQUARES][NUM_POSSIBLE_MOVES])
{
	unsigned char temp = 0;

	temp = lut[pos][first];
	lut[pos][first] = lut[pos][min];
	lut[pos][min] = temp;	
}

#endif


