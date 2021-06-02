#include <iostream>
#include <stdint.h>
#include <string>



using namespace std;


enum order {FIRST,SECOND};
enum type {HUMAN,CPU};
enum mode {STEALING, NO_STEALING};
enum level {EASY, MEDIUM, HARD};


struct choice
{
	mode selected_mode;
	level selected_level;
	order selected_order;
	uint8_t selected_time_limit;
};
choice receive_user_choice(void)
{
	choice user_choice;
	string received_input;
	bool repeat_selection = false;

	do
	{
		//delay(300);
		cout << "Please select game difficulty, type e for easy, m for medium, or h for hard.\n";
		cin >> received_input;

		if (received_input == "e" || received_input == "E")
		{
			user_choice.selected_level = EASY;
			cout << "You selected easy level, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input=="c" || received_input=="C") ? false: true;
		}

		else if (received_input == "m" || received_input == "M")
		{
			user_choice.selected_level = MEDIUM;
			cout << "You selected medium level, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input=="c" || received_input=="C") ? false: true;
		}

		else if (received_input == "h" || received_input == "H")
		{
			user_choice.selected_level = HARD;
			cout << "You selected hard level, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input=="c" || received_input=="C") ? false: true;
		}

		else
		{
			cout << "Invalid choice!! please enter only one of the 3 valid characters.\n";
			repeat_selection = true;
		}



	}while (repeat_selection);


	do
	{
		//delay(300);
		cout << "Please select game mode, type w for with-stealing mode or n for no-stealing mode.\n";
		cin >> received_input;

		if (received_input == "w" || received_input == "W")
		{
			user_choice.selected_mode = STEALING;
			cout << "You selected with-stealing mode, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input=="c" || received_input=="C") ? false: true;
		}

		else if (received_input == "n" || received_input == "N")
		{
			user_choice.selected_mode = NO_STEALING;
			cout << "You selected no-stealing mode, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input=="c" || received_input=="C") ? false: true;
		}


		else
		{
			cout << "Invalid choice!! please enter only one of the 2 valid characters.\n";
			repeat_selection = true;
		}



	}while (repeat_selection);


	do
	{
		//delay(300);
		cout << "Please select your turn order,  type f to be first player or s to be second player.\n";
		cin >> received_input;

		if (received_input == "f" || received_input == "F")
		{
			user_choice.selected_order= FIRST;
			cout << "You chose to be first player, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input=="c" || received_input=="C") ? false: true;
		}

		else if (received_input == "s" || received_input == "S")
		{
			user_choice.selected_order= SECOND;
			cout << "You chose to be second player, type c to confirm or anything else to repeat your choice.\n";
			cin >> received_input;
			repeat_selection = (received_input=="c" || received_input=="C") ? false: true;
		}


		else
		{
			cout << "Invalid choice!! please enter only one of the 2 valid characters.\n";
			repeat_selection = true;
		}



	}while (repeat_selection);


	cout << "Default CPU time limit is 5 seconds, press y to change it or anything else to keep it as default.\n";

	cin >> received_input;
	if (received_input == "y" || received_input == "Y")
	{

		do{
			//delay(300);
			repeat_selection = false;
			cout << "Please write the time limit in seconds.\n";
			cin >> received_input;

			for (uint8_t k=0; k<received_input.length(); k++)
			{
				if ( !(received_input[k] >= 48 && received_input[k] <= 57) )		// the digit is not from 0 to 9 since 0 in ASCHI is mapped to 48
				{
					cout << "Please do not write any letter, just write a number .\n";
					repeat_selection = true;
					break;

				}


			}

			if (repeat_selection == false)
				user_choice.selected_time_limit =  stoi(received_input);	// number is accepted



		}while (repeat_selection);



	}

	else												// keep time limit as default
		user_choice.selected_time_limit =  5;



	return user_choice;
}

int main(){
    receive_user_choice();
    return 0;
}