#ifndef ALGO_H
#define ALGO_H
//----------------------------------------------------------------------------------------------
// algo.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "defs.h"

#if !defined (MODEL_SIM)

class algo: public sc_module 
{

public:
	// Clock
	sc_in<bool> CLK;    
	sc_in<bool> reset;

	// Input ports
	sc_in<sc_int<ALGO_BITS> >  in_data; 
	sc_in<bool> data_valid;                       
	sc_in<bool> data_ack;
	
	// Output ports
	sc_out<sc_int<ALGO_BITS> > out_data;
	sc_out<bool> data_req;
	sc_out<bool> data_ready;       

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
	sc_int<ALGO_BITS> m_block_data[ALGO_BLOCK_SIZE];

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

	// Peak indicator
	sc_int<ALGO_BITS> m_peak;    // Local value for current peak

    /** 
      Processing data block. Performs Input gain, IIR filter and peak detector.

      Gain is performed on input signal x = g*input
      IIR filter (Biquad) y = a0*x + a1*x1 + a2*x2 - b0*y1 - b1*y2 
      Peak is detected on output signal y
      Algo processing time in cycles = ALGO_BLOCK_SIZE + 1
    */
	void AlgoProcess();		     // Process of algorithm

	void Entry();

public:
	SC_CTOR(algo)
	{
		SC_THREAD(Entry);	
		sensitive_pos << CLK;
	}

};      

#else
// Modelsim with VHDL simulation

class algo: public sc_foreign_module 
{

public:
	// Clock
	sc_in<bool> CLK;    
	sc_in<bool> reset;

	// Input ports
	sc_in<sc_int<ALGO_BITS> >  in_data; 
	sc_in<bool> data_valid;                       
	sc_in<bool> data_ack;
	
	// Output ports
	sc_out<sc_int<ALGO_BITS> > out_data;
	sc_out<bool> data_req;
	sc_out<bool> data_ready;       

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

    algo(sc_module_name nm, const char* hdl_name)
       : sc_foreign_module(nm),
       CLK("CLK"),
       reset("reset"),
       in_data("in_data"),
       data_valid("data_valid"),
       data_ack("data_ack"),
       out_data("out_data"),
       data_req("data_req"),
       data_ready("data_ready"),
       in_reg1("in_reg1"),
       in_reg2("in_reg2"),
       out_reg2("out_reg2"),
       in_coef0("in_coef0"),
       in_coef1("in_coef1"),
       in_coef2("in_coef2"),
       in_coef3("in_coef3"),
       in_coef4("in_coef4")
    {
       elaborate_foreign_module(hdl_name);
    }
    ~algo()
    {}

};      

#endif

#endif
