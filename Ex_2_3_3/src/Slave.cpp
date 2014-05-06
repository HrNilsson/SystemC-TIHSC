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
		ready.write(SC_LOGIC_1);

		for(int i = 0; i<10; i++) {
			while(valid.read() == SC_LOGIC_0) {
				wait();
			}
			cout << data.read() << endl;
			wait();
		}

		ready.write(SC_LOGIC_0);
		wait();
	}
}
