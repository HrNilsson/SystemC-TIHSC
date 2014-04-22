//BEGIN ADCSource.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ADCSource.h"

ADCSource::ADCSource(sc_module_name nm)
:   sc_module(nm),
	counter(0)
{
    SC_METHOD(SampleReady);
	sensitive << clk_in;
    dont_initialize();
}

void ADCSource::SampleReady(void)
{
	if (clk_in.read() == true)
	{
#if 0
		sc_uint<SAMPLE_BITS> d = rand()&0x3ffff;
#else
		sc_uint<SAMPLE_BITS> d = counter;
		counter += 1;
#endif
		data_out->write(d);
		busy_out->write(SC_LOGIC_1);
	}
	else
		busy_out->write(SC_LOGIC_0);
}

/**
void ADCSource::ADCThread(void)
{
	busy_out->write(SC_LOGIC_0);
	wait(400, SC_NS);

	for (unsigned i=0; i!=20; i++) 
	{
		sc_uint<SAMPLE_BITS> d = rand()&0x3ffff;
		data_out->write(d);
		busy_out->write(SC_LOGIC_1);
		wait(SAMPLE_PERIODE/2, SC_NS);
	
		busy_out->write(SC_LOGIC_0);
		wait(SAMPLE_PERIODE/2, SC_NS);
	}//endfor

}
**/

//end ADCSource


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: ADCSource.cpp,v 1.2 2004/02/02 12:08:16 dcblack Exp $
