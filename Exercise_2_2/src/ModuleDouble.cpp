#include "ModuleDouble.h"

using namespace std;

void ModuleDouble::A_th() {
	while (1) {
		wait(3, SC_MS);
		A_ev.notify();
		wait(A_timeout,Aack_ev);
	}
}

void ModuleDouble::B_th() {
	while (1) {
		wait(2, SC_MS);
		B_ev.notify();
		wait(B_timeout,Back_ev);
	}
}

void ModuleDouble::A_me() {
	if(event) {
		next_trigger(A_ev);
		cout << sc_time_stamp() << " event: B" << endl;
		event = false;
	} else {
		next_trigger(B_ev);
		cout << sc_time_stamp() << " event: A" << endl;
		event = true;
	}
}
