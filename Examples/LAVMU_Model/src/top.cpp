//----------------------------------------------------------------------------------------------
// top.cpp (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
#include "Algo.h"
#include "top.h"

Top::Top(sc_module_name nm) : 

	sc_module(nm),

	clock("clock", sc_time(CLK_PERIODE, SC_NS) ),
	AudioClock("AudioClock", sc_time(AUDIOCLK_PER, SC_NS) ),

	AudioIn("AudioIn"),
	AudioSync("AudioSync"),
	AudioOut("AudioOut")
{

	// Create instances
	
	pSource = new CodecSource("CodecSource");
	pAlgo = new algo("Algo");
	pSink = new CodecSink("CodecSink");
	pPView = new PView("PView");

	// Reset high
	reset.write(true);

	// Assign ports to channels 

	pAlgo->AudioSync(AudioSync);
	// Sample data input interface
	pAlgo->in_data(AudioIn);
	// Sample data output interface
	pAlgo->out_data(AudioOut);

	// Programmers View user register
	pAlgo->Reset(reset);
	pAlgo->in_reg1(in_reg1);
	pAlgo->in_reg2(in_reg2);
	pAlgo->out_reg2(out_reg2);
	pAlgo->in_coef0(in_coef0);
	pAlgo->in_coef1(in_coef1);
	pAlgo->in_coef2(in_coef2);
	pAlgo->in_coef3(in_coef3);
	pAlgo->in_coef4(in_coef4);
	pAlgo->CLK(clock.signal());
	pAlgo->AudioClk(AudioClock.signal());

	// Source to simulate audio input from codec
	pSource->Reset(reset);
	pSource->AudioIn(AudioIn);
	pSource->AudioSync(AudioSync);
	pSource->AudioClk(AudioClock.signal());
	 
	// Sink to simulate audio output to codec
	pSink->AudioOut(AudioOut);
	pSink->AudioSync(AudioSync);
	pSink->AudioClk(AudioClock.signal());

	// User to simulate Programmers View
	pPView->reset(reset);
	pPView->set_gain(in_reg1);
	pPView->set_user(in_reg2),
	pPView->get_peak(out_reg2);
	pPView->set_coeff0(in_coef0);
	pPView->set_coeff1(in_coef1);
	pPView->set_coeff2(in_coef2);
	pPView->set_coeff3(in_coef3);
	pPView->set_coeff4(in_coef4);
	pPView->CLK(clock.signal());

	// Create tacefile
	tracefile = sc_create_vcd_trace_file("LAVMU_Wave");
	if (!tracefile) cout << "Could not create trace file." << endl;

	// Set resolution of trace file to be in 10 US
	tracefile->set_time_unit(1, SC_NS);

	sc_trace(tracefile, clock.signal(), "clock");

	sc_trace(tracefile, AudioClock.signal(), "AudioClock");

	sc_trace(tracefile, reset, "reset");

	sc_trace(tracefile, in_reg2, "in_reg2");
	sc_trace(tracefile, in_coef0, "in_coef0");

	sc_trace(tracefile, AudioSync, "AudioSync");
	sc_trace(tracefile, AudioIn, "AudioIn");
	sc_trace(tracefile, AudioOut, "AudioOut");
}

Top::~Top()
{
	sc_close_vcd_trace_file(tracefile);

	cout << "Created LAVMU_Wave.vcd" << endl;
}
