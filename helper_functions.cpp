#include "helper_functions.h"

bool is_valid(int8_t* state, type player_type, uint8_t player_move)
{
	if (player_type == CPU && state[player_move - 1] == 0)
	{
		return false;
	}
	else if (player_type == HUMAN && state[player_move + 6] == 0)	// player_move -1+7
	{
		return false;
	}
	else
		return true;
}


state_info get_next_state(int8_t* state, mode playing_mode, type player_type, uint8_t player_move)
{
	state_info updated_state;
	updated_state.another_turn = false;
	updated_state.game_ended = false;
	uint8_t amount, i, total_count = 0, last_position;
	int8_t old_state[14];

	for (int i = 0; i < 14; i++)			// since we nedd to restore the original value of the state
		old_state[i] = state[i];

	if (player_type == CPU)
	{
		amount = state[player_move - 1];
		state[player_move - 1] = 0;
		for (i = 0;i < amount;i++)
		{
			if ((player_move + i) % 14 == 13)				// HUMAN mancala
			{
				amount++;
				continue;
			}
			state[(player_move + i) % 14]++;
		}

		last_position = (player_move + i - 1) % 14;

		if (playing_mode == STEALING)
		{
			if (state[last_position] == 1 && last_position < 6 && state[12 - last_position] != 0)			// last ball was thrown to an empty pocket of CPU
			{
				total_count = state[last_position] + state[12 - last_position];
				state[last_position] = 0;
				state[12 - last_position] = 0;								// opponent opposite pocket
				state[6] += total_count;									// CPU mancala balls increase
			}
		}

		if (state[0] == 0 && state[1] == 0 && state[2] == 0 && state[3] == 0 && state[4] == 0 && state[5] == 0) // last movement for CPU
		{
			updated_state.game_ended = true;
			total_count = 0;
			for (i = 0;i < 6;i++)
			{
				total_count += state[i + 7];												// put all remaining balls in HUMAN mancala
				state[i + 7] = 0;
			}

			state[13] += total_count;
		}

		else if (last_position == 6)									// last ball in CPU mancala
			updated_state.another_turn = true;
	}

	else if (player_type == HUMAN)
	{
		amount = state[player_move + 6];		// player_move -1+7
		state[player_move + 6] = 0;			// player_move -1+7
		for (i = 0;i < amount;i++)
		{
			if ((player_move + 7 + i) % 14 == 6)		// CPU mancala
			{
				amount++;
				continue;
			}
			state[(player_move + 7 + i) % 14]++;
		}

		last_position = (player_move + i + 6) % 14;

		if (playing_mode == STEALING)
		{
			if (state[last_position] == 1 && last_position > 6 && last_position < 13 && state[12 - last_position] != 0)			// last ball was thrown to an empty pocket of HUMAN
			{
				total_count = state[last_position] + state[12 - last_position];
				state[last_position] = 0;
				state[12 - last_position] = 0;								// opponent opposite pocket
				state[13] += total_count;									// HUMAN mancala balls increase
			}
		}

		if (state[7] == 0 && state[8] == 0 && state[9] == 0 && state[10] == 0 && state[11] == 0 && state[12] == 0) // last movement for HUMAN
		{
			updated_state.game_ended = true;
			total_count = 0;
			for (i = 0;i < 6;i++)
			{
				total_count += state[i];												// put all remaining balls in CPU mancala
				state[i] = 0;
			}

			state[6] += total_count;
		}

		else if (last_position == 13)										// last ball in HUMAN mancala
			updated_state.another_turn = true;
	}

	for (uint8_t h = 0; h < 14; h++)
		updated_state.state[h] = state[h];

	for (int i = 0; i < 14; i++)									// restoring the original value, this is necessary for minimax function
		state[i] = old_state[i];

	return updated_state;
}


void display_mancala(int8_t* state)
{
	cout << "\n  ______________________" << endl;

	cout << " |  |" << state[5] - 1 + 1 << '|' << state[4] - 1 + 1 << '|' << state[3] - 1 + 1 << '|';
	cout << state[2] - 1 + 1 << '|' << state[1] - 1 + 1 << '|' << state[0] - 1 + 1 << "|" << endl;

	cout << " |" << state[6] - 1 + 1 << "---------------" << state[13] - 1 + 1 << '|' << endl;

	cout << " |  |" << state[7] - 1 + 1 << '|' << state[8] - 1 + 1 << '|' << state[9] - 1 + 1 << '|';
	cout << state[10] - 1 + 1 << '|' << state[11] - 1 + 1 << '|' << state[12] - 1 + 1 << "|" << endl;

	cout << "  ______________________\n" << endl;
}

choice receive_user_choice(void)
{
	choice user_choice;
	string received_input;
	bool repeat_selection = false;

	do
	{
		delay(300);
		cout << "Please select game difficulty, type e for easy, m for medium, or h for hard.\n";
		cin >> received_input;

		if (received_input == "e" || received_input == "E")
		{
			user_choice.selected_level = EASY;
			cout << "You selected easy level, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input == "c" || received_input == "C") ? false : true;
		}
		else if (received_input == "m" || received_input == "M")
		{
			user_choice.selected_level = MEDIUM;
			cout << "You selected medium level, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input == "c" || received_input == "C") ? false : true;
		}
		else if (received_input == "h" || received_input == "H")
		{
			user_choice.selected_level = HARD;
			cout << "You selected hard level, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input == "c" || received_input == "C") ? false : true;
		}
		else
		{
			cout << "Invalid choice!! please enter only one of the 3 valid characters.\n";
			repeat_selection = true;
		}

	} while (repeat_selection);

	do
	{
		delay(300);
		cout << "Please select game mode, type w for with-stealing mode or n for no-stealing mode.\n";
		cin >> received_input;

		if (received_input == "w" || received_input == "W")
		{
			user_choice.selected_mode = STEALING;
			cout << "You selected with-stealing mode, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input == "c" || received_input == "C") ? false : true;
		}
		else if (received_input == "n" || received_input == "N")
		{
			user_choice.selected_mode = NO_STEALING;
			cout << "You selected no-stealing mode, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input == "c" || received_input == "C") ? false : true;
		}
		else
		{
			cout << "Invalid choice!! please enter only one of the 2 valid characters.\n";
			repeat_selection = true;
		}

	} while (repeat_selection);

	do
	{
		delay(300);
		cout << "Please select your turn order,  type f to be first player or s to be second player.\n";
		cin >> received_input;

		if (received_input == "f" || received_input == "F")
		{
			user_choice.selected_order = FIRST;
			cout << "You chose to be first player, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input == "c" || received_input == "C") ? false : true;
		}
		else if (received_input == "s" || received_input == "S")
		{
			user_choice.selected_order = SECOND;
			cout << "You chose to be second player, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input == "c" || received_input == "C") ? false : true;
		}
		else
		{
			cout << "Invalid choice!! please enter only one of the 2 valid characters.\n";
			repeat_selection = true;
		}

	} while (repeat_selection);

	cout << "Default CPU time limit is 5 seconds, press y to change it or anything else to keep it as default.\n";

	cin >> received_input;
	if (received_input == "y" || received_input == "Y")
	{
		do {
			delay(300);
			repeat_selection = false;
			cout << "Please write the time limit in seconds.\n";
			cin >> received_input;

			for (uint8_t k = 0; k < received_input.length(); k++)
			{
				if (!(received_input[k] >= 48 && received_input[k] <= 57))		// the digit is not from 0 to 9 since 0 in ASCHI is mapped to 48
				{
					cout << "Please do not write any letter, just write a number .\n";
					repeat_selection = true;
					break;
				}
			}

			if (repeat_selection == false)
				user_choice.selected_time_limit = stoi(received_input);	// number is accepted

		} while (repeat_selection);
	}

	else												// keep time limit as default
		user_choice.selected_time_limit = 5;

	return user_choice;
}


void delay(uint32_t milliseconds)			// OS independent
{
#ifdef _WIN32						// includes both 32 and 64 versions
	Sleep(milliseconds);
#endif
#ifdef __linux__
	usleep(milliseconds * 1000);
#endif
}

// score is calculated with respect to CPU
int Get_Score(int8_t state[])
{
	int CPU_Score = state[0] + state[1] + state[2] + state[3] + state[4] + state[5] + state[6];
	int HUMAN_Score = state[7] + state[8] + state[9] + state[10] + state[11] + state[12] + state[13];
	int score = CPU_Score - HUMAN_Score;
	return score;
}


void Get_next_state_indices(int8_t state[], int8_t indeces[], type player_type)
{
	if (player_type == CPU)
	{
		for (int i = 0; i < 6; i++)
		{
			if (state[i] == 0)
				indeces[i] = -1;
			else
				indeces[i] = i + 1;                          //to make indices between 1 and 6
		}
	}
	else
	{
		for (int i = 7; i < 13; i++)
		{
			if (state[i] == 0)
				indeces[i] = -1;
			else
				indeces[i] = i - 6;                          //to make indices between 1 and 6
		}
	}
}

int Mini_Max_Algo(state_info current_state, int depth, mode playing_mode, player_state stateOfPlayer, int alpha, int beta, int* Best_move_index, int check_index_value)
{
	if ((depth == 0) || (current_state.game_ended == 1))
		return Get_Score(current_state.state);

	int8_t indeces[6];
	if (stateOfPlayer == Maximizing)
		Get_next_state_indices(current_state.state, indeces, CPU);
	else
		Get_next_state_indices(current_state.state, indeces, HUMAN);

	if (stateOfPlayer == Maximizing)
	{

		for (int i = 0; i < 6; i++)
		{
			if (indeces[i] == -1)
				continue;
			else
			{
				//now i have the first child for root node
				state_info child = get_next_state(current_state.state, playing_mode, CPU, indeces[i]);

				int val;
				if (current_state.another_turn == 1)
					val = Mini_Max_Algo(child, depth - 1, playing_mode, Maximizing, alpha, beta, Best_move_index, 0);
				else
					val = Mini_Max_Algo(child, depth - 1, playing_mode, Minimizing, alpha, beta, Best_move_index, 0);

				if (val > alpha)
				{
					alpha = val;
					if (check_index_value == 1)
					{
						*Best_move_index = indeces[i];
					}
				}

				if (beta <= alpha)
					break;
			}
		}
		return alpha;
	}
	else {

		for (int i = 0; i < 6; i++)
		{
			if (indeces[i] == -1)
				continue;
			else
			{
				//now i have the first child for root node
				state_info child = get_next_state(current_state.state, playing_mode, HUMAN, indeces[i]);
				int val;

				if (current_state.another_turn == 1)
					val = Mini_Max_Algo(child, depth - 1, playing_mode, Minimizing, alpha, beta, Best_move_index, 0);
				else
					val = Mini_Max_Algo(child, depth - 1, playing_mode, Maximizing, alpha, beta, Best_move_index, 0);

				beta = (beta < val) ? beta : val;
				if (beta <= alpha)
					break;
			}
		}
		return beta;
	}
}
