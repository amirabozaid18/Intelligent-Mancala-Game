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
void receive_user_choice(void)
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

}
int main(){
    receive_user_choice();
    return 0;
}