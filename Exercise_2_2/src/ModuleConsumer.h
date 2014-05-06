#ifndef MODULE_CONSUMER_H_
#define MODULE_CONSUMER_H_
#include <systemc.h>
#include "ModuleProducer.h"

SC_MODULE (ModuleConsumer)
{
	sc_fifo_in<TCPHeader*> fifo_in;

	void Consumer_th();

	SC_CTOR(ModuleConsumer) {
		SC_THREAD(Consumer_th);
	}
};

#endif /* MAC_H_ */
