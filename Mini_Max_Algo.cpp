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
