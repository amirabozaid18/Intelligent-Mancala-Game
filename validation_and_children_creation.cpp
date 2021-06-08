#include <stdint.h>

enum type {HUMAN, CPU};

bool is_valid(int8_t* state, type player_type, uint8_t player_move)
{
	if (player_type == CPU && state[player_move - 1] == 0)
		return false;
	else if (player_type == HUMAN && state[player_move + 6 ] == 0)	// player_move is -1+7
		return false;
	else
		return true;
}

void Get_next_state_indices(int8_t state[], int8_t indices[], type player_type)
{
	if (player_type == CPU)
	{
		for (int i = 0; i < 6; i++)
		{
			if (state[i] == 0)
				indices[i] = -1;
			else
				indices[i] = i + 1;	// make indices between 1 and 6
		}
	}
	else
	{
		for (int i = 7; i < 13; i++)
		{
			if (state[i] == 0)
				indices[i] = -1;
			else
				indices[i] = i - 6 ;	// make indices between 1 and 6
		}
	}
}
