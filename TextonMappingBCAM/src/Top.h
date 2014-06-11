
#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>
#include "CPU.h"
#include "KMeans.h"

SC_MODULE (Top)
{
	CPU cpu;
	KMeans kMeans;

	sc_signal<float*> imageFilteredSig;
	sc_signal<int*> textonSig;

	sc_signal<bool> kMeansDone;

	sc_trace_file *tracefile;

	SC_CTOR(Top): cpu("CPU"), kMeans("K-Means"), kMeansDone("kMeansDone")
	{
		cpu.imageFilteredSig(imageFilteredSig);
		kMeans.imageFilteredSig(imageFilteredSig);

		cpu.textonSig(textonSig);
		kMeans.textonSig(textonSig);

		cpu.kMeansDone(kMeansDone);
		kMeans.kMeansDone(kMeansDone);

		// Create tacefile
		tracefile = sc_create_vcd_trace_file("streamingWave");
		if (!tracefile) cout << "Could not create trace file." << endl;

		// Set resolution of trace file
		tracefile->set_time_unit(1, SC_NS);

		/*sc_trace(tracefile, imageFilteredSig, "imageFilteredSig");
		sc_trace(tracefile, textonSig, "textonSig");
		sc_trace(tracefile, kMeansDone, "kMeansDone");*/

	}

	~Top()
	{
		sc_close_vcd_trace_file(tracefile);

		cout << "Created streamingWave.vcd" << endl;
	}

};


#endif
