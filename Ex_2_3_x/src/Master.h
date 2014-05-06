/*
 * Master.h
 *
 *  Created on: May 6, 2014
 *      Author: rene
 */

#ifndef MASTER_H_
#define MASTER_H_

#include <systemc.h>
#include "defs.h"

SC_MODULE (Master)
{
	sc_in_clk CLK;
	
	sc_in<sc_logic> ready;
	sc_out<sc_logic> valid;

	sc_out<sc_int<CHANNEL_BITS> > channel;
	sc_out<sc_int<ERROR_BITS> > error;
	sc_out<sc_int<DATA_BITS> > data;

	void transmit_th();

	SC_CTOR(Master) {
		SC_THREAD(transmit_th);
			sensitive << CLK.pos();
	}
};

#endif /* MASTER_H_ */
