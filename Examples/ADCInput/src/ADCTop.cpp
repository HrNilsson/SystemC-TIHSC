//BEGIN ADCTop.cpp (systemc)
// Asynchronous input buffer with 4-128 samples of n bit width
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ADCTop.h"

ADCTop::ADCTop(sc_module_name nm)
: sc_module(nm),
#if (SC_API_VERSION_STRING == sc_api_version_2_2_0)
	clock("clock", sc_time(SAMPLE_PERIODE/2, SC_NS) ),
#else
	clock("clock", SAMPLE_PERIODE/2, 0.5, 0.0, false),
#endif
	clk("clk"),
	busy("busy"),
	inData("inData"),
	read("read"),
	ready("ready"),
	outData("outData")
{
	// Create instances
	pADC = new ADCSource("ADC7631");
	pBuffer = new CirBuffer("CircularBuf");
	pPowerPC = new PowerPC("PowerPC");

	// Connect ports to channels

	// ADC output
	pADC->clk_in(clk);
	pADC->busy_out(busy);
	pADC->data_out(inData);

	// Buffer input interface
	pBuffer->busy_in(busy);
	pBuffer->data_in(inData);

	// Buffer output interface
	pBuffer->read_in(read);
	pBuffer->ready_out(ready);
	pBuffer->data_out(outData);

	// PowerPC input
	pPowerPC->read_out(read);
	pPowerPC->ready_in(ready);
	pPowerPC->data_in(outData);

	// Assign connection between clock and channel
	SC_METHOD(ClockSignal);
    sensitive << clock.signal();
    dont_initialize();

	// Create tacefile
	tracefile = sc_create_vcd_trace_file("ADCInputWave");
	if (!tracefile) cout << "Could not create trace file." << endl;

	sc_trace(tracefile, clk, "clk");
	sc_trace(tracefile, busy, "busy");
	sc_trace(tracefile, inData, "inData");
	sc_trace(tracefile, read, "read");
	sc_trace(tracefile, ready, "ready");
	sc_trace(tracefile, outData, "outData");
}

ADCTop::~ADCTop()
{
	sc_close_vcd_trace_file(tracefile);
	cout << "Created ADCInputWave.vcd" << endl;
}

void ADCTop::ClockSignal()
{
    sc_logic clock_tmp(clock.signal().read());
    clk.write(clock_tmp);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: ADCTop.cpp,v 1.2 2004/02/02 12:08:16 dcblack Exp $
