#include "ModuleSingle.h";

void ModuleSingle::increment() {
	using namespace std;
	counter++;
	cout << counter << endl;
}

void ModuleSingle::notify() {
	while (1) {
		increment_event.notify();
		wait(2, SC_MS);
	}
}
