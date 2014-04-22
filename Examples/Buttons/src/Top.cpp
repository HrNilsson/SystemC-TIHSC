//----------------------------------------------------------------------------------------------
// Top.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Top test bench for debounce button input detector

#include "Buttons.h"
#include "Top.h"

Top::Top(sc_module_name nm) : sc_module(nm),

#if (SC_API_VERSION_STRING == sc_api_version_2_2_0)
	clock("clock", sc_time(CLK_PERIODE, SC_US) ),
#else
	clock("clock", CLK_PERIODE, 0.5, 0.0, false),
#endif

	clk("clk"),
	
	input1("input1"),
	input2("input2"),
	input3("input3"),
	input4("input4"),
	input5("input5"),

	output1("output1"),
	output2("output2"),
	output3("output3"),
	output4("output4"),
	output5("output5")

{
	// Create instances
	pSimuli = new Simuli("Simuli");
	pButtons = new Buttons("Buttons");
	pMonitor = new Monitor("Monitor");

	// Create input and ouput pointers
	input[0] = &input1;
	input[1] = &input2;
	input[2] = &input3;
	input[3] = &input4;
	input[4] = &input5;

	output[0] = &output1;
	output[1] = &output2;
	output[2] = &output3;
	output[3] = &output4;
	output[4] = &output5;

	// Connect ports to channels

	// Simuli ports
	pButtons->clk(clk);
	pSimuli->clk_in(clk);


	for (unsigned i = 0; i < N_BUTTONS; i++)
	{
		pSimuli->sim_out[i](*input[i]);

		// Buttons ports
		pButtons->input[i](*input[i]);
		pButtons->output[i](*output[i]);

		// Monitor ports
		pMonitor->input[i](*output[i]);
	}

	// Assign connection between clock and channel
	SC_METHOD(ClockSignal);
    sensitive << clock.signal();
    dont_initialize();

	// Create tacefile
	tracefile = sc_create_vcd_trace_file("DebounceWave");
	if (!tracefile) cout << "Could not create trace file." << endl;

	// Set resolution of trace file to be in 10 US
	tracefile->set_time_unit(1, SC_NS);

	sc_trace(tracefile, clk, "clk");

	sc_trace(tracefile, input1, "input1");
	sc_trace(tracefile, input2, "input2");
	sc_trace(tracefile, input3, "input3");
	sc_trace(tracefile, input4, "input4");
	sc_trace(tracefile, input5, "input5");

	sc_trace(tracefile, output1, "output1");
	sc_trace(tracefile, output2, "output2");
	sc_trace(tracefile, output3, "output3");
	sc_trace(tracefile, output4, "output4");
	sc_trace(tracefile, output5, "output5");
}

Top::~Top()
{
	sc_close_vcd_trace_file(tracefile);
	cout << "Created DebounceWave.vcd" << endl;
}

void Top::ClockSignal()
{
    bool clock_tmp(clock.signal().read());
    clk.write(clock_tmp);
}
