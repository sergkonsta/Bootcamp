/*
Developer: Sergey Konstantinovsky
Date:      21.06.2020
Reviewer:  Jenia	
*/
#include <assert.h>	/*for assert*/

#include "bit_array.h"
#include "knights_tour.h"

#define NUM_OF_POSITIONS (NUM_OF_ROWS * NUM_OF_COLUMNS)
#define NUM_POSSIBLE_MOVES (8)
#define NUM_OF_ROWS (8)
#define NUM_OF_COLUMNS (8)
#define INVALID_INDEX (NUM_OF_POSITIONS + 1)
#define UNUSED(x) (void)(x)

typedef enum status
{
	SUCCESS,
	FAIL
} status_t;

static void InitLUTImp(unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES]);
static status_t TourImp(unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES], 
					unsigned char curr_pos, bit_arr_t steps_made, unsigned char *res_path);

#ifdef HEURISTIC
static size_t CountValidMovesImp(unsigned char curr_pos, bit_arr_t steps_made,
				unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES]);
static size_t NextMinImp(unsigned char curr_pos, bit_arr_t steps_made, 
				unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES]); 
static void SwapMovesImp(size_t first, size_t min, unsigned char curr_pos,
				unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES]);
#endif



/*----------------------------------------------------------------------------*/
int KnightsTour(unsigned char init_pos, unsigned char *res_path)
{
	bit_arr_t steps_made = 0;
	
	unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES] = {0};
	
	assert(NULL != res_path);

	InitLUTImp(move_map);	
	
	return (int)TourImp(move_map, init_pos, steps_made, res_path);
}



/*----------------------------------------------------------------------------*/
static status_t TourImp(unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES], 
					unsigned char curr_pos, bit_arr_t steps_made, unsigned char *res_path)
{
	size_t move_number = 0;
	size_t next_min_idx = 0;
	
	/*mark that knight stepped here*/
	steps_made = BArrSetOn(steps_made, curr_pos);

	/*stop when all positions has been visited*/
	if (NUM_OF_POSITIONS == BArrCountOn(steps_made))
	{
		*res_path = curr_pos;
		return 0;
	}

	/*arranges moves in move_map: moves with least possible moves - come first*/
	#ifdef HEURISTIC
	next_min_idx = NextMinImp(curr_pos, steps_made, move_map);
	if (INVALID_INDEX != next_min_idx)
	{
		SwapMovesImp(0, next_min_idx, curr_pos, move_map);
	}
	#else
	UNUSED(next_min_idx);
	#endif

	/*check all possible next moves for current position*/
	while (INVALID_INDEX != move_map[curr_pos][move_number] && 		
			move_number < NUM_POSSIBLE_MOVES)
	{
		/*call yourself if haven't been stepped on*/
		if (0 == BArrGetVal(steps_made, move_map[curr_pos][move_number]) &&
			0 == TourImp(move_map, move_map[curr_pos][move_number], 
						steps_made, res_path + 1))
		{
			*res_path = curr_pos;
			return SUCCESS;
		}

		++move_number;
	}

	return FAIL;
}


#ifdef HEURISTIC
/*----------------------------------------------------------------------------*/
/* 
returns amount of valid moves from current position
*/
static size_t CountValidMovesImp(unsigned char curr_pos, bit_arr_t steps_made,
				unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES])
{
	size_t i = 0;
	size_t counter = 0;

	for (i = 0; INVALID_INDEX != move_map[curr_pos][i] && i < NUM_POSSIBLE_MOVES; ++i)
	{
		if (0 == BArrGetVal(steps_made, move_map[curr_pos][i]))
		{
			++counter;
		}
	}

	return counter;
}

/*----------------------------------------------------------------------------*/
/* find next move with least possibilties and return its index */
static size_t NextMinImp(unsigned char curr_pos, bit_arr_t steps_made, 
						unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES]) 
{
	size_t index_min_possibilities = NUM_OF_POSITIONS;
	size_t num_of_min_options = 0;
	size_t num_of_options = 0;
	size_t i = 0;

	for (i = 0; i < NUM_POSSIBLE_MOVES && INVALID_INDEX != move_map[curr_pos][i]; ++i)
	{
		if  (0 == BArrGetVal(steps_made, move_map[curr_pos][i]))
		{
			num_of_options = CountValidMovesImp(move_map[curr_pos][i], steps_made, move_map);

			/* if first possible move , store it */
			if (NUM_OF_POSITIONS == index_min_possibilities && (0 < num_of_options))
			{
				num_of_min_options = num_of_options;
				index_min_possibilities = i;
			}
			/* if current possible move have less next moves than previous
			   found store it */
			else if (NUM_OF_POSITIONS != index_min_possibilities && 
				(0 < num_of_options) && (num_of_options < num_of_min_options)) 
			{
				num_of_min_options = num_of_options;
				index_min_possibilities = i;
			}
		}
	}

	return index_min_possibilities;
}

/*----------------------------------------------------------------------------*/
static void SwapMovesImp(size_t first, size_t min, unsigned char curr_pos,
				    unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES])
{
	unsigned char temp = 0;

	temp = move_map[curr_pos][first];
	move_map[curr_pos][first] = move_map[curr_pos][min];
	move_map[curr_pos][min] = temp;	
}

#endif



/*----------------------------------------------------------------------------*/
/*
inits move_map with knights move types, 
no heuristics,
an invalid move initialized with the value of NUM_OF_POSITIONS
*/
static void InitLUTImp(unsigned char move_map[NUM_OF_POSITIONS][NUM_POSSIBLE_MOVES])
{
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < NUM_OF_POSITIONS; ++i)
	{
		for (j = 0; j < NUM_POSSIBLE_MOVES; ++j)
		{
			move_map[i][j] = INVALID_INDEX;
		}
	}

	for (i = 0; i < NUM_OF_POSITIONS; ++i)
	{
		j = 0;

		if (i > 16 && i % NUM_OF_ROWS > 0)
		{
			move_map[i][j] = i - 17;
			++j;
		}
		if (i >= 16 && i % NUM_OF_ROWS < 7)
		{
			move_map[i][j] = i - 15;
			++j;
		}
		if (i > 8 && i % NUM_OF_ROWS > 1)
		{
			move_map[i][j] = i - 10;
			++j;
		}

		if (i >= 8 && i % NUM_OF_ROWS < 6)
		{
			move_map[i][j] = i - 6;
			++j;
		}

		if (i < 56 && i % NUM_OF_ROWS > 1)
		{
			move_map[i][j] = i + 6;
			++j;
		}

		if (i < 56 && i % NUM_OF_ROWS < 6)
		{
			move_map[i][j] = i + 10;
			++j;
		}

		if (i < 48 && i % NUM_OF_ROWS > 0)
		{
			move_map[i][j] = i + 15;
			++j;
		}

		if (i < 48 && i % NUM_OF_ROWS < 7)
		{
			move_map[i][j] = i + 17;
			++j;
		}
	}
}


