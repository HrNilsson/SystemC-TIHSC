//----------------------------------------------------------------------------------------------
// source.h (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
#include "defs.h"

class CodecSource: public sc_module
{
public:
	// Clock
	sc_in_clk AudioClk;

	// Ports
	sc_in<bool> Reset;
	sc_out<sc_int<ALGO_BITS> >  AudioIn;
	sc_out<bool> AudioSync;

	void entry();

	SC_CTOR(CodecSource)
    {
      SC_THREAD(entry);
	  sensitive_pos << AudioClk;
   	  dont_initialize();
    }

	~CodecSource()
	{
	  fclose(fp_left);
	  fclose(fp_right);
	}

private:
	FILE *fp_left;
	FILE *fp_right;

};
