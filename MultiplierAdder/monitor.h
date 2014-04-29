/*
 * monitor.h
 *
 *  Created on: Apr 30, 2013
 *      Author: kbe
 */

#ifndef MONITOR_H_
#define MONITOR_H_
#include <iomanip>
using std::setw;
#include <systemc.h>


SC_MODULE (Monitor)
{
	sc_in<int> f;

	sc_in<bool> clk;

	void thread(){
        int expected = 30;

        // Monitoring output from MAC operation
        // based on stimulus data
		while(1) {
			wait();
			cout << name() << setw(8) << f << " " << setw(8) << sc_time_stamp() << endl;
			sc_assert(f == expected);
			if (expected <= 50) expected += 10;
		}

	}

	SC_CTOR(Monitor) {
		SC_THREAD(thread);
		sensitive << clk.neg();
	}
};

#endif /* MONITOR_H_ */
