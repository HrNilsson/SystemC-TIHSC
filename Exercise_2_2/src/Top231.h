/*
 * Top231.h
 *
 *  Created on: May 2, 2014
 *      Author: rene
 */

#ifndef TOP231_H_
#define TOP231_H_
#include <systemc.h>

#include "ModuleProducer.h"
#include "ModuleConsumer.h"

SC_MODULE (Top231)
{
	sc_fifo<TCPHeader*> fifo_c1;
	sc_fifo<TCPHeader*> fifo_c2;
	sc_clock clock;

	ModuleProducer p;
	ModuleConsumer c1, c2;

	SC_CTOR(Top231):
		clock("clock", sc_time(20, SC_NS)), fifo_c1("fifo_c1",5), fifo_c2("fifo_c2",5), c1("Consumer1"),
		c2("Consumer2"), p("Producer")
	{
		// Connect signals to ports
		p.out(fifo_c1);
		p.out(fifo_c2);
		c1.fifo_in(fifo_c1);
		c2.fifo_in(fifo_c2);
	}

};

#endif /* TOP231_H_ */
