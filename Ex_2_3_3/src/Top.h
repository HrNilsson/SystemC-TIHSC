
#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>
#include "Master.h"
#include "Slave.h"

SC_MODULE (Top)
{
	sc_clock clock;

	Master m;
	Slave s;

	sc_signal<sc_logic> ready;
	sc_signal<sc_logic> valid;
	sc_signal<sc_int<CHANNEL_BITS> > channel;
	sc_signal<sc_int<ERROR_BITS> > error;
	sc_signal<sc_int<DATA_BITS> > data;

	sc_trace_file *tracefile;

	SC_CTOR(Top): clock("clock", sc_time(20, SC_NS)), m("Master"), s("Slave"),
			ready("ready"), valid("valid"), channel("channel"), error("error"), data("data")
	{
		s.CLK(clock);
		s.ready(ready);
		s.valid(valid);
		s.data(data);
		s.error(error);
		s.channel(channel);


		m.CLK(clock);
		m.ready(ready);
		m.valid(valid);
		m.data(data);
		m.error(error);
		m.channel(channel);

		// Create tacefile
		tracefile = sc_create_vcd_trace_file("streamingWave");
		if (!tracefile) cout << "Could not create trace file." << endl;

		// Set resolution of trace file
		tracefile->set_time_unit(1, SC_NS);

		sc_trace(tracefile, clock, "clock");

		sc_trace(tracefile, ready, "ready");

		sc_trace(tracefile, valid, "valid");
		sc_trace(tracefile, data, "data");

		sc_trace(tracefile, error, "error");
		sc_trace(tracefile, channel, "channel");

	}

	~Top()
	{
		sc_close_vcd_trace_file(tracefile);

		cout << "Created streamingWave.vcd" << endl;
	}

};


#endif
