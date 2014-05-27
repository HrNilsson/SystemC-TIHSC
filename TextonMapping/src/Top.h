
#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>
#include "CPU.h"
#include "KMeans.h"

SC_MODULE (Top)
{
	int texton[96516];
	float* image_output;

	CPU cpu;
	KMeans kMeans;

	sc_signal<bool> filterDone;

	sc_trace_file *tracefile;

	SC_CTOR(Top): cpu("CPU",image_output, texton), kMeans("K-Means", texton, image_output)
	{

		cpu.filterDone(filterDone);
		kMeans.filterDone(filterDone);

		// Create tacefile
		tracefile = sc_create_vcd_trace_file("streamingWave");
		if (!tracefile) cout << "Could not create trace file." << endl;

		// Set resolution of trace file
		tracefile->set_time_unit(1, SC_NS);

		sc_trace(tracefile, clock, "clock");


	}

	~Top()
	{
		sc_close_vcd_trace_file(tracefile);

		cout << "Created streamingWave.vcd" << endl;
	}

};


#endif
