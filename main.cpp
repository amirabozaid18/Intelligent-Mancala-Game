
#include "helper_functions.h"



int main()
{
	int the_best_move = -1;
	uint8_t selected_depth;
	choice user_choice;
	uint8_t selected_move;
	string received_string = "";
	bool human_another_turn = false;
	bool cpu_another_turn = false;
	int8_t initial_state[14] = { 4,4,4,4,4,4,0,4,4,4,4,4,4,0 };
	state_info next_info;

	for (uint8_t h = 0; h < 14; h++)
		next_info.state[h] = initial_state[h];


	cout << "Welcome to MANCALA, We hope you enjoy this game.\n\n";
	delay(1000);
	user_choice = receive_user_choice();

	if (user_choice.selected_level == EASY)
		selected_depth = 3;
	else if (user_choice.selected_level == MEDIUM)
		selected_depth = 7;
	else if (user_choice.selected_level == HARD)
		selected_depth = 15;

	cout << "Game will begin in 5 seconds, please know that your left most pocket number is 1 and your right most pocket is 6.\n";
	delay(5000);
	display_mancala(next_info.state);


	if (user_choice.selected_order == FIRST)
	{
		while (1)
		{
			do
			{
				human_another_turn = false;
				delay(1000);
				cout << "your turn, please select one of non-empty pockets of you\n";
				cin >> received_string;
				if (received_string == "1" || received_string == "2" || received_string == "3" || received_string == "4" || received_string == "5" || received_string == "6")
				{
					selected_move = stoi(received_string);
					if ( is_valid(next_info.state,HUMAN,selected_move))
					{
						next_info = get_next_state(next_info.state,user_choice.selected_mode,HUMAN,selected_move);
						display_mancala(next_info.state);

						if (next_info.another_turn)
							human_another_turn = true;

					}

					else				// invalid_choice
					{
						cout << "invalid choice, use only valid numbers of non-empty pockets\n";
						human_another_turn = true;
					}
				}

				else
				{
					cout << "invalid choice, use only valid numbers from 1 to 6 and not strings\n";
					human_another_turn = true;
				}

			}while(human_another_turn);



			if (next_info.game_ended)
			{
				cout << "Game over, ";

				if ((next_info.state)[13] < 24)			// HUMAN MANCALA balls are less than 24
					cout << "CPU is the winner.\n";
				else if ((next_info.state)[13] == 24)
					cout << "draw.\n";
				else		//>24
					cout << "You are the winner.\n";

				break;
			}


			do
			{
				cpu_another_turn = false;
				delay(1000);
				cout << "CPU turn, please wait";
				Mini_Max_Algo(next_info,selected_depth, user_choice.selected_mode, Maximizing, -INFINITY, INFINITY,&the_best_move,1);
				next_info = get_next_state(next_info.state,user_choice.selected_mode,CPU,the_best_move);
				the_best_move = -1;
				if (user_choice.selected_level == EASY || user_choice.selected_level == MEDIUM)
					delay((user_choice.selected_time_limit) *1000);
				else		// hard
					delay(( (user_choice.selected_time_limit) *1000) - 500);		// assume hard mode calculations take 500ms
				display_mancala(next_info.state);

				if (next_info.another_turn)
				{
					delay(300);
					cpu_another_turn = true;
				}

			}while(cpu_another_turn);


			if (next_info.game_ended)
			{
				cout << "Game over, ";

				if ((next_info.state)[13] < 24)			// HUMAN MANCALA balls are less than 24
					cout << "CPU is the winner.\n";
				else if ((next_info.state)[13] == 24)
					cout << "draw.\n";
				else		//>24
					cout << "You are the winner.\n";

				break;
			}


		}

	}

	else if (user_choice.selected_order == SECOND)
	{
		selected_move = 4;
		while (1)
		{

			do
			{
				cpu_another_turn = false;
				delay(1000);
				cout << "CPU turn, please wait";
				Mini_Max_Algo(next_info,selected_depth, user_choice.selected_mode, Maximizing, -INFINITY, INFINITY,&the_best_move,1);
				next_info = get_next_state(next_info.state,user_choice.selected_mode,CPU,the_best_move);
				the_best_move = -1;
				if (user_choice.selected_level == EASY || user_choice.selected_level == MEDIUM)
					delay((user_choice.selected_time_limit) *1000);
				else		// hard
					delay(( (user_choice.selected_time_limit) *1000) - 500);		// assume hard mode calculations take 500ms
				display_mancala(next_info.state);

				if (next_info.another_turn)
				{
					delay(300);
					cpu_another_turn = true;
				}

			}while(cpu_another_turn);


			if (next_info.game_ended)
			{
				cout << "Game over, ";

				if ((next_info.state)[13] < 24)			// HUMAN MANCALA balls are less than 24
					cout << "CPU is the winner.\n";
				else if ((next_info.state)[13] == 24)
					cout << "draw.\n";
				else		//>24
					cout << "You are the winner.\n";

				break;
			}


			do
			{
				human_another_turn = false;
				delay(1000);
				cout << "your turn, please select one of non-empty pockets of you\n";
				cin >> received_string;
				if (received_string == "1" || received_string == "2" || received_string == "3" || received_string == "4" || received_string == "5" || received_string == "6")
				{
					selected_move = stoi(received_string);
					if ( is_valid(next_info.state,HUMAN,selected_move))
					{
						next_info = get_next_state(next_info.state,user_choice.selected_mode,HUMAN,selected_move);
						display_mancala(next_info.state);

						if (next_info.another_turn)
							human_another_turn = true;

					}

					else				// invalid_choice
					{
						cout << "invalid choice, use only valid numbers of non-empty pockets\n";
						human_another_turn = true;
					}
				}

				else
				{
					cout << "invalid choice, use only valid numbers from 1 to 6 and not strings\n";
					human_another_turn = true;
				}

			}while(human_another_turn);



			if (next_info.game_ended)
			{
				cout << "Game over, ";

				if ((next_info.state)[13] < 24)			// HUMAN MANCALA balls are less than 24
					cout << "CPU is the winner.\n";
				else if ((next_info.state)[13] == 24)
					cout << "draw.\n";
				else		//>24
					cout << "You are the winner.\n";

				break;
			}

		}

	}



	return 0;
}


