#include "Top.h"


int sc_main(int argc, char* argv[])
{
	time_t timer1, timer2;
	double seconds;

	using namespace std;
	cout << "Simulation started" << endl;
	time(&timer1);

	Top top("Top");
	sc_start();

	time(&timer2);
	cout << "Simulation ended" << endl;

	seconds = difftime(timer2,timer1);
	cout << "Time elapsed: " << seconds << " seconds." << endl;

	return 0;

}
