#ifndef POWERPC_H
#define POWERPC_H
//BEGIN PowerPC.h (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "CirBuffer.h"

#ifdef _EA_IMPORT

class PowerPC : public sc_module
{
public:

#else

SC_MODULE(PowerPC) 
{

#endif

  // Input interface
  sc_out<bool> read_out;				// Read stobe for data in buffer
  sc_in<bool> ready_in;					// Ready signal when data_out valid
  sc_in<sc_uint<SAMPLE_BITS> > data_in;	// Data ouput from buffer

  SC_CTOR(PowerPC);

  // Thread to simulate PowerPC empties buffer
  void Simulate();

};

#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: async_mem.h,v 1.2 2004/04/15 17:37:04 dcblack Exp $
