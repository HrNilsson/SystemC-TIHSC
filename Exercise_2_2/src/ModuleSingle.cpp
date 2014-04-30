#include "ModuleSingle.h";

void ModuleSingle::increment() {
	counter++;
}

void ModuleSingle::notify() {
	while (1) {

		wait(2, SC_MS);
	}
}
