//============================================================================
// Name        : SynFir.c
// Author      : Kim Bjerge
// Version     : 25. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized FIR filter design using templates
// 				 This is a timed model (SystemC for SystemCrafterSC)
//============================================================================
#ifndef SC_GATELEVEL
#include <systemc.h>
#endif

#include "Defs.h"
#include "SynFir.h"

void SynFir::DoCalculate()
{
	sc_int<ALGO_BITS*2> sum;
	bool clock_state;

	while(true)
	{			
		// Check if reset is active (async. reset)
		if (reset == true)
		{
			for (unsigned i=0; i < TABS; i++)
			{
				m_delay_line[i] = 0;
				m_coeffs[i] = 0;
				wait();
			}
			clock_state = true;
		}
		else
		{				
			// Check for positive edge of sample clock
			if (sample_clock.read() == 1)
			{
				if (clock_state == false)
				{
					// Shift samples within delay line
					for (int j = TABS-1; j > 0; j--)
					{
						m_delay_line[j] = m_delay_line[j-1];
						wait();
					}
					
					//sum = in_data.read();
					
					// Read new data sample
					m_delay_line[0] = in_data.read();
					
					// Compute fir output
					sum = 0;
					for (int i=0; i < TABS; i++)
					{
						sum += m_delay_line[i] * m_coeffs[i];
						wait();
					}
					
					sum >>= (ALGO_BITS-1);
					
					out_data.write(sum);						
					clock_state = true;
				}
			}
			else
			{
				// Update coefficients
				m_coeffs[0] = in_coef0;
				m_coeffs[1] = in_coef1;
				m_coeffs[2] = in_coef2;
				m_coeffs[3] = in_coef3;
				m_coeffs[4] = in_coef4;
				m_coeffs[5] = in_coef5;
				m_coeffs[6] = in_coef6;
				m_coeffs[7] = in_coef7;
				m_coeffs[8] = in_coef8;
				m_coeffs[9] = in_coef9;
				m_coeffs[10] = in_coef10;
				m_coeffs[11] = in_coef11;
				m_coeffs[12] = in_coef12;
				m_coeffs[13] = in_coef13;
				m_coeffs[14] = in_coef14;
				m_coeffs[15] = in_coef15;
				m_coeffs[16] = in_coef16;
				m_coeffs[17] = in_coef17;
				m_coeffs[18] = in_coef18;
				m_coeffs[19] = in_coef19;
				m_coeffs[20] = in_coef20;
				m_coeffs[21] = in_coef21;
				m_coeffs[22] = in_coef22;
		
				clock_state = false; 
			}				
		}
			
		// Wait for next pos edge of clock
		wait();
	}
}
