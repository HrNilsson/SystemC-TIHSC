/*
 * stimulus.h
 *
 *  Created on: Apr 30, 2013
 *      Author: kbe
 */

#ifndef STIMULUS_H_
#define STIMULUS_H_
#include <systemc.h>

SC_MODULE (Stimulus)
{
	sc_out<int> a, b, c;

	sc_in<bool> clk;

	void generate();

	SC_CTOR(Stimulus) {
		SC_THREAD(generate);
		sensitive << clk.pos();
	}
};

#endif /* STIMULUS_H_ */
