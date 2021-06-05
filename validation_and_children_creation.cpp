#include <iostream>
#include <stdint.h>

enum type {HUMAN, CPU};
enum mode {STEALING, NO_STEALING};

struct state_info
{
	int8_t state[14];
	bool another_turn;
	bool game_ended;
	int score;
};

struct arrays_collection
{
	state_info children[6];
};

bool is_valid(int8_t* state, type player_type, uint8_t player_move)
{
	if (player_type == CPU && state[player_move - 1] == 0)
		return false;
	else if (player_type == HUMAN && state[player_move + 6 ] == 0)	// player_move is -1+7
		return false;
	else
		return true;
}

arrays_collection get_children(int8_t* state, mode playing_mode, type player_type)
{
	arrays_collection result;
	int8_t* obtained_child;
	
	// tracking state's original value, it will change at calling get_next_state()
	uint8_t old_state[14];			

	for(uint8_t u = 0; u < 14; u++)
		old_state[u] = state[u];

	for (uint8_t k = 0; k < 6; k++)
	{
		if (is_valid(state, player_type, k + 1))
		{
			//obtained_child = get_next_state(state, playing_mode, player_type, k + 1).state;
			for(uint8_t h = 0; h < 14; h++)
				(((result.children)[k]).state)[h] = obtained_child[h];
		}
		else	//invalid child due to invalid move
			(((result.children)[k]).state)[0] = -1;
			
		for(uint8_t u = 0; u < 14; u++)
			state[u] = old_state[u];	// restoring the original value of the state
	}
	return result;
}
