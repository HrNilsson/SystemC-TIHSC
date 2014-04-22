#ifndef ADCSOURCE_H
#define ADCSOURCE_H
//BEGIN ADCSource.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "CirBuffer.h"

#define SAMPLE_PERIODE 400 // Sample periode in nS (250 kSPS = 4000 ns)

#ifdef _EA_IMPORT

class ADCSource : public sc_module
{
public:

#else

SC_MODULE(ADCSource) 
{

#endif

	// Local channels
	sc_in<sc_logic> clk_in;
	sc_out<sc_logic> busy_out;
	sc_out<sc_lv<SAMPLE_BITS> > data_out;

	// Test variables
	sc_uint<SAMPLE_BITS> counter;
	CirBuffer *m_CirBuffer;
 
	SC_CTOR(ADCSource);

	// Test source thread
	void ADCThread();

	void SampleReady(void);

};

#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: ADCSource.h,v 1.2 2004/04/15 17:37:04 dcblack Exp $
