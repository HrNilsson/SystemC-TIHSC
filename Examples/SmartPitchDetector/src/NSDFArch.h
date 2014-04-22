#ifndef NSDFArch_H_
#define NSDFArch_H_
//============================================================================
// Name        : NSFD.h
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector  design using templates
// 				 This is an untimed model
//			     Calculates the normalized squared difference function
//============================================================================
#define SC_INCLUDE_FX
#include <systemc.h>
#include <math.h>

/**
 * Template Parameters:
 * 	class T - specifies the data-type used within the algorithm
 * 	T must be a numeric type that supports:
 * 		operator==(const T&)
 * 		operator=(int)
 * 		operator+=(const T&)
 * 		operator*(const T&)
 * 	unsigned W - specifies the window size of the pitch detector
 * 		W must be greater than zero
 * 
 *  Constructor parameters:
 * 		sc_module_name name - specifies instance name
 **/


class NSDFArch : public sc_module
{
public:
	sc_in<bool> clock; // Clock
	sc_in<bool> reset; // Reset
	sc_in<bool> sample_clock; // Sample clock
	sc_in<sc_int<ALGO_BITS> >  in_data; // Input port 
	sc_out<sc_int<ALGO_BITS> > out_data; // Output port
	
public:	

	SC_CTOR(NSDFArch)
	{
		SC_THREAD(DoCalculate);
		sensitive_pos << sample_clock;
		idx = 0;
	}
	
private:
	
	unsigned idx;
	sc_int<ALGO_BITS> m_x[WINDOW]; 	// Window of input samples
	sc_int<ALGO_BITS> r_tau[WINDOW]; // Autocorrelation ACF type II (ACF)
	sc_int<ALGO_BITS> m_tau[WINDOW]; // Squared difference function modified SDF (SDF)
	sc_int<ALGO_BITS> n_tau[WINDOW]; // Normalized squared difference function (NSDF)
	sc_int<ALGO_BITS> sample;
	
	void DoCalculate();
};

#endif /*NSDFArch_H_*/
