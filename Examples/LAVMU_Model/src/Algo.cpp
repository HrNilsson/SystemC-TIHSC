//----------------------------------------------------------------------------------------------
// algo.cpp (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
// This is the implementation of the algorithm
#include "Algo.h"

/** 
   Algo entry function
*/
void algo::Entry()
{ 
	// Variable Declarations
	sc_int<ALGO_BITS> tmp_data;
	bool AudioSync_last = false;

	// Thread loop
	cout << "Algo started" << endl;
	while(true)
	{ 
		// Check if reset is active
		if (Reset == true)
		{
			// Initialization of algorithm
			// Clear IIR
			m_x1 = 0;
			m_x2 = 0;
			m_y1 = 0;
			m_y2 = 0;
		}
		else
		{
			if (AudioSync == true && AudioSync_last == false)
			{
				// Right channel
				m_sample = in_data.read();
				AlgoProcess();
				out_data.write(m_sample);

			}
			if (AudioSync == false && AudioSync_last == true)
			{
				// Left channel
				m_sample = in_data.read();
				AlgoProcess();
				out_data.write(m_sample);
			}
			AudioSync_last = AudioSync;
		}

		wait();
	}      

}

/** 
  Processing data block. Performs Input gain, IIR filter and peak detector.

  Gain is performed on input signal x = g*input
  IIR filter (Biquad) y = a0*x + a1*x1 + a2*x2 - b0*y1 - b1*y2 
  Peak is detected on output signal y
  Algo processing time in cycles = ALGO_BLOCK_SIZE + 1
*/
void algo::AlgoProcess()
{
	sc_int<ALGO_BITS> tmp_in;
	sc_int<ALGO_BITS*2> tmp_out;
	
	// Read gain
	int in_gain = in_reg1.read();

	// Read input register 2
	int reg2 = in_reg2.read();

	// Check enable iir filter
	int enable_iir = reg2 & ENABLE_IIR_BIT;

	// Read IIR coefficients
	m_coef0 = in_coef0.read();
	m_coef1 = in_coef1.read();
	m_coef2 = in_coef2.read();
	m_coef3 = in_coef3.read();
	m_coef4 = in_coef4.read();

		
	// Mulitply gain on input sample
	tmp_in = m_sample * in_gain;
	tmp_out = tmp_in;

	if (enable_iir == ENABLE_IIR_BIT)
	{
		// IIR filter (Biquad) y = b0*x + b1*x1 + b2*x2 - a0*y1 - a1*y2
		tmp_out =   m_coef0 * tmp_in
				  + m_coef1 * m_x1
				  + m_coef2 * m_x2
				  - m_coef3 * m_y1
				  - m_coef4 * m_y2;

		// Scale filter
		tmp_out >>= (ALGO_BITS-1);
		//tmp_out >>= ALGO_BITS;

		// Save Z values
		m_x2 = m_x1;
		m_x1 = tmp_in;
		m_y2 = m_y1;
		m_y1 = tmp_out;
	}

	// Save output
	m_sample = tmp_out;

}
