#ifndef MODULE_DOUBLE_H_
#define MODULE_DOUBLE_H_
#include <systemc.h>

SC_MODULE (ModuleDouble)
{
	sc_event A_ev, B_ev, Aack_ev, Back_ev;
	sc_time A_timeout = sc_time(3, SC_MS);
	sc_time B_timeout = sc_time(2, SC_MS);
	bool event = true;

	void A_th();
	void B_th();
	void A_me();

	SC_CTOR(ModuleDouble) {
		SC_THREAD(A_th);
		SC_THREAD(B_th);
		SC_METHOD(A_me);
			sensitive << B_ev;
			dont_initialize();
	}
};

#endif /* MAC_H_ */
