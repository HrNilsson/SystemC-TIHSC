//----------------------------------------------------------------------------------------------
// top.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include "algo.h"
#include "top.h"

Top::Top(sc_module_name nm) : 

	sc_module(nm),

	clock("clock", sc_time(CLK_PERIODE, SC_NS) ),

	in_data("in_data"),
	data_valid("data_valid"),
	data_ack("data_ack"),

	out_data("out_data"),
	data_req("data_req"),
	data_ready("data_ready")
{

	// Create instances
	
	pSource = new source("Source");
#if defined(MODEL_SIM)
	pAlgo = new algo("Algo","work.algo");
#else
	pAlgo = new algo("Algo");
#endif
	pSink = new sink("Sink");
	pUser = new user("User");

	// Reset high
	reset.write(true);

	// Assign ports to channels 

	// Sample data input interface
	pAlgo->in_data(in_data);
	pAlgo->data_valid(data_valid);
	pAlgo->data_ack(data_ack);
	
	// Sample data output interface
	pAlgo->out_data(out_data);
	pAlgo->data_req(data_req);
	pAlgo->data_ready(data_ready);

	// Programmers View user register
	pAlgo->reset(reset);
	pAlgo->in_reg1(in_reg1);
	pAlgo->in_reg2(in_reg2);
	pAlgo->out_reg2(out_reg2);
	pAlgo->in_coef0(in_coef0);
	pAlgo->in_coef1(in_coef1);
	pAlgo->in_coef2(in_coef2);
	pAlgo->in_coef3(in_coef3);
	pAlgo->in_coef4(in_coef4);
	pAlgo->CLK(clock.signal());

	// Source to simulate input sample data
	pSource->data_req(data_req);
	pSource->out_data(in_data);
	pSource->data_valid(data_valid);
	pSource->CLK(clock.signal());
	 
	// Sink to simulate output sample data
	pSink->data_ready(data_ready);
	pSink->data_ack(data_ack);
	pSink->in_data(out_data);
	pSink->CLK(clock.signal());

	// User to simulate Programmers View
	pUser->reset(reset);
	pUser->set_gain(in_reg1);
	pUser->set_user(in_reg2),
	pUser->get_peak(out_reg2);
	pUser->set_coeff0(in_coef0);
	pUser->set_coeff1(in_coef1);
	pUser->set_coeff2(in_coef2);
	pUser->set_coeff3(in_coef3);
	pUser->set_coeff4(in_coef4);
	pUser->CLK(clock.signal());

	// Create tacefile
	tracefile = sc_create_vcd_trace_file("AlgoWave");
	if (!tracefile) cout << "Could not create trace file." << endl;

	// Set resolution of trace file to be in 10 US
	tracefile->set_time_unit(1, SC_NS);

	sc_trace(tracefile, clock.signal(), "clock");

	sc_trace(tracefile, reset, "reset");

	sc_trace(tracefile, in_reg2, "in_reg2");
	sc_trace(tracefile, in_coef0, "in_coef0");

	sc_trace(tracefile, in_data, "in_data");
	sc_trace(tracefile, data_valid, "data_valid");
	sc_trace(tracefile, data_ack, "data_ack");

	sc_trace(tracefile, out_data, "out_data");
	sc_trace(tracefile, data_req, "data_req");
	sc_trace(tracefile, data_ready, "data_ready");
}

Top::~Top()
{
	sc_close_vcd_trace_file(tracefile);

	cout << "Created AlgoWave.vcd" << endl;
}
