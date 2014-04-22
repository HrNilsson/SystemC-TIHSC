//----------------------------------------------------------------------------------------------
// CodecSink.h (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "defs.h"

class CodecSink: public sc_module
{
public:
	// Clock
	sc_in_clk AudioClk;

	// Reset
	sc_in<bool>  AudioSync;

	// Audio source output
	sc_in< sc_int<ALGO_BITS> > AudioOut;

private:
	// File handle to store data
	// in left and right channels
	FILE* fp_left;
	FILE* fp_right;

	void entry(); 

public:
	SC_CTOR(CodecSink)
	{
		SC_THREAD(entry);
		sensitive_pos << AudioClk;
   	    dont_initialize();
	}

	~CodecSink()
	{
	  fclose(fp_left);
	  fclose(fp_right);
	}
};
