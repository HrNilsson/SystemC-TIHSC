#ifndef MODULE_SINGLE_H_
#define MODULE_SINGLE_H_
#include <systemc.h>

SC_MODULE (ModuleSingle)
{
	sc_uint<4> counter = 0;
	sc_event increment_event;

	void increment();
	void notify();

	SC_CTOR(ModuleSingle) {
		SC_METHOD(increment);
		sensitive << increment_event;
		SC_THREAD(notify);
	}
};

#endif /* MAC_H_ */
