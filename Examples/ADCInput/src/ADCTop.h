#ifndef ADCTOP_H
#define ADCTOP_H
//BEGIN ADCInput.h (systemc)
// Asynchronous input buffer with 4-128 samples of n bit width
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "ADCSource.h"
#include "CirBuffer.h"
#include "PowerPC.h"

#ifdef _EA_IMPORT

class ADCTop : public sc_module
{
public:

#else

SC_MODULE(ADCTop) 
{

#endif
	sc_clock clock;								// Sample clock

	// Channels between ADCSource and ADCInput
	sc_signal<sc_logic> clk;					// Sample clock channel to ADC
	sc_signal<sc_logic> busy;					// Logical high (1) when new din sample
	sc_signal<sc_lv<SAMPLE_BITS> > inData;		// Data input from ADC

	// Output interface
	sc_signal<bool> read;						// Read stobe for data in buffer
	sc_signal<bool> ready;						// Ready signal when data_out valid
	sc_signal<sc_uint<SAMPLE_BITS> > outData;	// Data ouput from buffer

	// Modules and Components 
	ADCSource *pADC;
	CirBuffer *pBuffer;
	PowerPC *pPowerPC;

	sc_trace_file *tracefile;

	SC_CTOR(ADCTop);
	~ADCTop();

	void ClockSignal();

};

#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: ADCTop.h,v 1.2 2004/04/15 17:37:04 dcblack Exp $
