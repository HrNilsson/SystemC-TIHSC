/*
 * Slave.h
 *
 *  Created on: May 6, 2014
 *      Author: rene
 */

#ifndef SLAVE_H_
#define SLAVE_H_

#include <systemc.h>
#include "defs.h"

SC_MODULE (Slave)
{

	sc_in_clk CLK;

	sc_out<sc_logic> ready;
	sc_in<sc_logic> valid;
	sc_in<sc_int<CHANNEL_BITS> > channel;
	sc_in<sc_int<ERROR_BITS> > error;
	sc_in<sc_int<DATA_BITS> > data;
	
	void receive_th();

	SC_CTOR(Slave) {
		SC_THREAD(receive_th);
			sensitive << CLK.neg();
	}
};


#endif /* SLAVE_H_ */
