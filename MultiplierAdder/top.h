/*
 * top.h
 *
 *  Created on: Apr 30, 2013
 *      Author: kbe
 */

#ifndef TOP_H_
#define TOP_H_
#include <systemc.h>

#include "mac.h"
#include "stimulus.h"
#include "monitor.h"

SC_MODULE (Top)
{
	sc_signal<int> s_a, s_b, s_c, s_f;
	sc_clock clock;

	Stimulus *pStim;
	Mac *pMac;
	Monitor *pMonitor;
	sc_trace_file *tf;

	SC_CTOR(Top):
		clock("clock", sc_time(20, SC_NS)) // 50 Mhz clock
	{
		// Creates modules
		pStim = new Stimulus("Stimulus");
		pMac = new Mac("MAC");
		pMonitor = new Monitor("Monitor");

		// Connect signals to ports
		pStim->a(s_a);
		pStim->b(s_b);
		pStim->c(s_c);
		pStim->clk(clock);
		pMac->a(s_a);
		pMac->b(s_b);
		pMac->c(s_c);
		pMac->f(s_f);
		pMonitor->clk(clock);
		pMonitor->f(s_f);

		// Create VCD wave form file used for signal timing analysis
		tf = sc_create_vcd_trace_file("WaveForm");
		tf->set_time_unit(1, SC_NS);
		sc_trace(tf, s_a, "a");
		sc_trace(tf, s_b, "b");
		sc_trace(tf, s_c, "c");
		sc_trace(tf, s_f, "f");
		sc_trace(tf, clock.signal(), "clock");

	}

	~Top()
	{
		sc_close_vcd_trace_file(tf);
		delete pStim;
		delete pMac;
		delete pMonitor;
	}

};

#endif /* TOP_H_ */
