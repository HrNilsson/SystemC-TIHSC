//----------------------------------------------------------------------------------------------
// source.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include "defs.h"

class source: public sc_module 
{
public:
	// Clock
	sc_in_clk CLK;   

	// Ports
	sc_in<bool> data_req; 
	sc_out<sc_int<ALGO_BITS> >  out_data;       
	sc_out<bool> data_valid;

	void entry();

	SC_CTOR(source)
    {
      SC_THREAD(entry);
	  sensitive_pos << CLK;
   	  dont_initialize();
    }

};
