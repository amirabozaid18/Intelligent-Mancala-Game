@@ -1,43 +0,0 @@
#include <iostream>
#include <stdint.h>


#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif

using namespace std;


void display_mancala(int8_t* state)
{

	cout << "\n  ______________________" << endl;

	cout << " |  |" << state[5] -1+1 << '|' << state[4]-1+1 << '|'<< state[3] -1+1 << '|';
	cout << state[2] -1+1 << '|'<< state[1] -1+1<< '|'<< state[0] -1+1 << "|" << endl;

	cout << " |" << state[6] -1+1 << "---------------" << state[13] -1+1 << '|' << endl;

	cout << " |  |" << state[7] -1+1 << '|' << state[8]-1+1 << '|'<< state[9] -1+1 << '|';
	cout << state[10] -1+1 << '|'<< state[11] -1+1<< '|'<< state[12] -1+1 << "|" << endl;

	cout << "  ______________________\n" << endl;
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