/*
 * Master.cpp
 *
 *  Created on: May 6, 2014
 *      Author: rene
 */

#include "Master.h"

void Master::transmit_th() {

	valid.write(SC_LOGIC_0);

	while(1) {
		while(ready.read() == SC_LOGIC_0) {
			wait();
		}

		channel.write(0);
		error.write(0);
		data.write(234);
		valid.write(SC_LOGIC_1);

		wait();

	}
}
