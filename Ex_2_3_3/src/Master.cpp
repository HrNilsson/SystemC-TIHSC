/*
 * Master.cpp
 *
 *  Created on: May 6, 2014
 *      Author: rene
 */

#include "Master.h"

void Master::transmit_th() {

	int i = 0;
	valid.write(SC_LOGIC_0);
	wait();

	while(1) {
		while(ready.read() == SC_LOGIC_0) {
			valid.write(SC_LOGIC_0);
			wait();
		}

		channel.write(0);
		error.write(0);
		data.write(i);
		valid.write(SC_LOGIC_1);

		wait();
		i++;

	}
}
