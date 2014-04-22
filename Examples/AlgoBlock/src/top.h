#ifndef TOP_H
#define TOP_H
//----------------------------------------------------------------------------------------------
// top.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "defs.h"
#include "sink.h"
#include "source.h"
#include "user.h"
#include "algo.h"

class Top : public sc_module
{
public:
	// Sample clock
	sc_clock clock;								
	sc_signal<bool> reset; // Reset signal

	// Input channels/signals
	sc_signal<sc_int<ALGO_BITS> > in_data;		
	sc_signal<bool> data_valid;
	sc_signal<bool> data_ack;

	// Output channels/signals
	sc_signal<sc_int<ALGO_BITS> > out_data;		
	sc_signal<bool> data_req;
	sc_signal<bool> data_ready;

	// Programmers View - User registers
	sc_signal<sc_int<WBUS> >  in_reg1;  // Input register (Set Gain)
	sc_signal<sc_int<WBUS> >  in_reg2;  // Input register (Clear Peak)
	sc_signal<sc_int<WBUS> >  out_reg2; // Output register (Get Peak)

	sc_signal<sc_int<WBUS> >  in_coef0;  // Input register (IIR coefficients)
	sc_signal<sc_int<WBUS> >  in_coef1;  // Input register (IIR coefficients)
	sc_signal<sc_int<WBUS> >  in_coef2;  // Input register (IIR coefficients)
	sc_signal<sc_int<WBUS> >  in_coef3;  // Input register (IIR coefficients)
	sc_signal<sc_int<WBUS> >  in_coef4;  // Input register (IIR coefficients)


private:
	// Modules and Components 
	source *pSource;
	algo *pAlgo;
	sink *pSink;
	user *pUser;

	sc_trace_file *tracefile;

public:
	SC_CTOR(Top);
	~Top();

};

#endif
