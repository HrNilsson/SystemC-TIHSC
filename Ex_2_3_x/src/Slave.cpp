/*
 * Slave.cpp
 *
 *  Created on: May 6, 2014
 *      Author: rene
 */

#include "Slave.h"
using namespace std;

void Slave::receive_th() {

	ready.write(SC_LOGIC_0);

	while(1) {
		wait();
		wait();
		wait();
		ready.write(SC_LOGIC_1);

		while(valid.read() == SC_LOGIC_0) {
			wait();
		}
		cout << data.read() << endl;
	}
}
