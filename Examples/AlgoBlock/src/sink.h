//----------------------------------------------------------------------------------------------
// sink.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "defs.h"

class sink: public sc_module 
{
public:
	// Clock
	sc_in_clk CLK;

	// Handshake ports
	sc_in<bool>  data_ready; 
	sc_out<bool> data_ack; 

	// Input data port
	sc_in< sc_int<ALGO_BITS> > in_data; 

private:
	// File handle to store result
	FILE* fp_data;

	void entry(); 

public:
	SC_CTOR(sink)
	{
		SC_THREAD(entry);
		sensitive_pos << CLK;
   	    dont_initialize();
	}

	~sink()
	{
	  fclose(fp_data);
	}
};
