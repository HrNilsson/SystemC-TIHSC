//----------------------------------------------------------------------------------------------
// algo.h (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "defs.h"


class algo: public sc_module 
{

public:
	// Clock
	sc_in<bool> CLK;    
	sc_in<bool> Reset;

	// Input ports
	sc_in<sc_int<ALGO_BITS> >  in_data; 
	
	// Output ports
	sc_out<sc_int<ALGO_BITS> > out_data;

	sc_in<bool> AudioSync;

	sc_in<bool> AudioClk;

	// Programmers View (User parameters)
	// Should be mapped to memory space of processor
	sc_in<sc_int<WBUS> >  in_reg1;   // Input register (Set Gain)

	sc_in<sc_int<WBUS> >  in_reg2;   // Input register 
									 // CLEAR_PEAK_BIT - Clear Peak indicator
									 // ENABLE_IIR_BIT - Enable IIR filter

	sc_out<sc_int<WBUS> >  out_reg2; // Output register (Read Peak)

	sc_in<sc_int<WBUS> >  in_coef0;  // IIR coefficients a0
	sc_in<sc_int<WBUS> >  in_coef1;  // IIR coefficients a1
	sc_in<sc_int<WBUS> >  in_coef2;  // IIR coefficients a2
	sc_in<sc_int<WBUS> >  in_coef3;  // IIR coefficients b0
	sc_in<sc_int<WBUS> >  in_coef4;  // IIR coefficients b1

private:
	// Local sample buffer
	sc_int<ALGO_BITS> m_sample;

	// IIR filter
	sc_int<ALGO_BITS> m_x1;
	sc_int<ALGO_BITS> m_x2;
	sc_int<ALGO_BITS> m_y1;
	sc_int<ALGO_BITS> m_y2;
	sc_int<WBUS> m_coef0;
	sc_int<WBUS> m_coef1;
	sc_int<WBUS> m_coef2;
	sc_int<WBUS> m_coef3;
	sc_int<WBUS> m_coef4;

    /** 
      IIR filter.

      Gain is performed on input signal x = g*input
      IIR filter (Biquad) y = a0*x + a1*x1 + a2*x2 - b0*y1 - b1*y2 
      Peak is detected on output signal y
    */
	void AlgoProcess();		     // Process of algorithm

	void Entry();

public:
	SC_CTOR(algo)
	{
		SC_THREAD(Entry);	
		sensitive_pos << AudioClk;
	}

};      
