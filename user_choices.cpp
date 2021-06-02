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
