

#include <stdint.h>



enum type {HUMAN,CPU};
enum mode {STEALING, NO_STEALING};

struct state_info
{
	int8_t state[14];
	bool another_turn;
	bool game_ended;
	int score;
};



state_info get_next_state(int8_t* state,mode playing_mode,type player_type,uint8_t player_move)
{
	state_info updated_state;
	updated_state.another_turn = false;
	updated_state.game_ended = false;
	uint8_t amount,i,total_count=0,last_position;


	if (player_type == CPU)
	{
		amount = state[player_move-1];
		state[player_move - 1] = 0;
		for(i=0;i<amount;i++)
		{
			if ( (player_move + i) % 14 == 13)				// HUMAN mancala
			{
				amount++;
				continue;
			}
			state[(player_move + i) % 14]++;
		}

		last_position =  (player_move + i - 1) % 14;


		if (playing_mode == STEALING)
		{
			if ( state[last_position] == 1 && last_position < 6)			// last ball was thrown to an empty pocket of CPU
			{
				total_count = state[last_position] + state[12 - last_position];
				state[last_position] = 0;
				state[12 - last_position ] = 0;								// opponent opposite pocket
				state[6] += total_count;									// CPU mancala balls increase
			}
		}

		if ( state[0]==0 && state[1]==0 && state[2]==0 && state[3]==0 && state[4]==0 && state[5]==0 ) // last movement for CPU
		{
			updated_state.game_ended = true;
			for (i=0;i<6;i++)
			{
				total_count += state[i+7];												// put all remaining balls in HUMAN mancala
				state[i+7] = 0;
			}


			state[13] += total_count;
		}

		else if ( last_position == 6)									// last ball in CPU mancala
			updated_state.another_turn = true;




	}

	else if (player_type == HUMAN)
	{
		amount = state[player_move+6];		// player_move -1+7
		state[player_move +6 ] = 0;			// player_move -1+7
		for(i=0;i<amount;i++)
		{
			if ( (player_move +7 + i) % 14 == 6)		// CPU mancala
			{
				amount++;
				continue;
			}
			state[(player_move + 7 + i) % 14]++;
		}

		last_position = (player_move + i + 6) % 14;


		if (playing_mode == STEALING)
		{
			if ( state[last_position] == 1 && last_position > 6 && last_position < 13)			// last ball was thrown to an empty pocket of HUMAN
			{
				total_count = state[last_position] + state[12 - last_position];
				state[last_position] = 0;
				state[12 - last_position ] = 0;								// opponent opposite pocket
				state[13] += total_count;									// HUMAN mancala balls increase
			}
		}

		if ( state[7]==0 && state[8]==0 && state[9]==0 && state[10]==0 && state[11]==0 && state[12]==0 ) // last movement for HUMAN
		{
			updated_state.game_ended = true;
			for (i=0;i<6;i++)
			{
				total_count += state[i];												// put all remaining balls in CPU mancala
				state[i] = 0;
			}


			state[6] += total_count;
		}

		else if ( last_position == 13)										// last ball in HUMAN mancala
			updated_state.another_turn = true;

	}

	for(uint8_t h=0; h<14; h++)
		updated_state.state[h] = state[h];

	return updated_state;
}




