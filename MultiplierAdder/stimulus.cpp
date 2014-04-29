/*
 * stimulus.cpp
 *
 *  Created on: Apr 30, 2013
 *      Author: kbe
 */
#include "stimulus.h"

void Stimulus::generate()
{
	// Generating input test data
	wait();
	a = 10; b = 2; c = 10;
    wait();
	a = 10; b = 3; c = 10;
    wait();
	a = 10; b = 4; c = 10;
    wait();
	a = 10; b = 5; c = 10;
}
