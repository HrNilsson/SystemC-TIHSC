/*
 * Master.cpp
 *
 *  Created on: May 6, 2014
 *      Author: rene
 */

#include "Master.h"

void Master::transmit_th() {

	int i = 0;
	
	while(1) {
		out.write(i);
		i++;

	}
}
