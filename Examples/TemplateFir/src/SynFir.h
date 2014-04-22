#ifndef SYNFIR_H_
#define SYNFIR_H_
//============================================================================
// Name        : SynFir.h
// Author      : Kim Bjerge
// Version     : 25. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized FIR filter design using templates
// 				 This is a timed model (SystemC for SystemCrafterSC)
//============================================================================
#include "Defs.h"

//#define SC_GATELEVEL

class SynFir : public sc_module
{
public:
	
	sc_in<bool> clock; // Clock
	sc_in<bool> reset; // Reset
	sc_in<bool> sample_clock; // Sample clock
	sc_in<sc_int<ALGO_BITS> >  in_data; // Input port 
	sc_out<sc_int<ALGO_BITS> > out_data; // Output port
	
	// Needed to add the coefficients
	sc_in<sc_int<WBUS> >  in_coef0;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef1;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef2;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef3;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef4;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef5;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef6;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef7;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef8;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef9;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef10;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef11;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef12;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef13;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef14;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef15;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef16;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef17;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef18;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef19;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef20;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef21;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef22;  // FIR coefficients
	
private:
	sc_int<ALGO_BITS> m_delay_line[TABS];
	sc_int<WBUS> m_coeffs[TABS];
	
	void DoCalculate();
	
public:	
	
	SC_CTOR(SynFir)
	{
		SC_THREAD(DoCalculate);
		sensitive_pos << clock;
	}
	
};

#else

// Modelsim with VHDL simulation
class SynFir : public sc_foreign_module
{
public:

	sc_in<bool> clock; // Clock
	sc_in<bool> reset; // Reset
	sc_in<bool> sample_clock; // Sample clock
	sc_in<sc_int<ALGO_BITS> >  in_data; // Input port
	sc_out<sc_int<ALGO_BITS> > out_data; // Output port

	// Needed to add the coefficients
	sc_in<sc_int<WBUS> >  in_coef0;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef1;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef2;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef3;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef4;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef5;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef6;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef7;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef8;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef9;   // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef10;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef11;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef12;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef13;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef14;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef15;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef16;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef17;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef18;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef19;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef20;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef21;  // FIR coefficients
	sc_in<sc_int<WBUS> >  in_coef22;  // FIR coefficients

    SynFir(sc_module_name nm, const char* hdl_name)
       : sc_foreign_module(nm),
       clock("clock"),
       reset("reset"),
       sample_clock("sample_clock"),
       in_data("in_data"),
       out_data("out_data"),
       in_coef0("in_coef0"),
       in_coef1("in_coef1"),
       in_coef2("in_coef2"),
       in_coef3("in_coef3"),
       in_coef4("in_coef4"),
       in_coef5("in_coef5"),
       in_coef6("in_coef6"),
       in_coef7("in_coef7"),
       in_coef8("in_coef8"),
       in_coef9("in_coef9"),
       in_coef10("in_coef10"),
       in_coef11("in_coef11"),
       in_coef12("in_coef12"),
       in_coef13("in_coef13"),
       in_coef14("in_coef14"),
       in_coef15("in_coef15"),
       in_coef16("in_coef16"),
       in_coef17("in_coef17"),
       in_coef18("in_coef18"),
       in_coef19("in_coef19"),
       in_coef20("in_coef20"),
       in_coef21("in_coef21"),
       in_coef22("in_coef22")
    {
       elaborate_foreign_module(hdl_name);
    }

    ~SynFir()
    {}

};

#endif /*SYNFIR_H_*/

