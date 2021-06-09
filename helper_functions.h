
#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include <iostream>
#include <stdint.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif


#define INFINITY 500

using namespace std;

enum order { FIRST, SECOND };
enum type { HUMAN, CPU };
enum mode { STEALING, NO_STEALING };
enum level { EASY, MEDIUM, HARD };
enum player_state { Minimizing, Maximizing };


struct state_info
{
	int8_t state[14];
	bool another_turn;
	bool game_ended;
};


struct arrays_collection
{
	state_info children[6];
};


struct choice
{
	mode selected_mode;
	level selected_level;
	order selected_order;
	uint8_t selected_time_limit;
};

bool is_valid(int8_t* state, type player_type, uint8_t player_move);
state_info get_next_state(int8_t* state, mode playing_mode, type player_type, uint8_t player_move);
void Get_next_state_indices(int8_t state[], int8_t indeces[], type player_type);
void display_mancala(int8_t* state);
choice receive_user_choice(void);
void delay(uint32_t milliseconds);
int Get_Score(int8_t state[]);
int Mini_Max_Algo(state_info current_state, int depth, mode playing_mode, player_state stateOfPlayer, int alpha, int beta, int* Best_move_index, int check_index_value);



#endif /* HELPER_FUNCTIONS_H_ */

