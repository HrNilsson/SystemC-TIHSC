
#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>
#include "Master.h"
#include "Slave.h"

SC_MODULE (Top)
{
	sc_clock clock;
	sc_signal<sc_logic> reset;

	Master m;
	Slave s;
	InAdapter<int, 16> a;

	//sc_fifo<int> fifo;

	sc_signal<sc_logic> ready;
	sc_signal<sc_logic> valid;
	sc_signal<sc_int<CHANNEL_BITS> > channel;
	sc_signal<sc_int<ERROR_BITS> > error;
	sc_signal<sc_int<DATA_BITS> > data;

	sc_trace_file *tracefile;

	SC_CTOR(Top): clock("clock", sc_time(20, SC_NS)), reset("reset"), m("Master"), s("Slave"), a("InAdapter"),
			ready("ready"), valid("valid"), channel("channel"), error("error"), data("data")
	{
		reset.write(false);

		s.CLK(clock);
		s.ready(ready);
		s.valid(valid);
		s.data(data);
		s.error(error);
		s.channel(channel);

		a.clock(clock);
		a.reset(reset);
		a.ready(ready);
		a.valid(valid);
		a.data(data);
		a.error(error);
		a.channel(channel);

		m.CLK(clock);
		m.out(a);

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
