//----------------------------------------------------------------------------------------------
// algo.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
// This is the implementation of the algorithm
#include "algo.h"

/** 
   Algo entry function
*/
void algo::Entry()
{ 
	// Variable Declarations
	sc_int<ALGO_BITS> tmp_data;
	short index;

	wait();

	// Thread loop
	while(true)
	{ 

		// Check if reset is active
		if (reset == true)
		{
			// Initialization of algorithm
			// Clear peak
			m_peak = 0;

			// Clear IIR
			m_x1 = 0;
			m_x2 = 0;
			m_y1 = 0;
			m_y2 = 0;

			data_req.write(false);
			data_ready.write(false);
		}
		else
		{

#ifdef _ALGO_DEBUG
			//Read in the Sample values
			cout << endl << "Reading in the samples..." << endl;
#endif

			// Reads input data block
			index = 0; 
			while( index < ALGO_BLOCK_SIZE )
			{
				// Signal request for data
				data_req.write(true);
				// Wait for valid data input
				do { wait(); } while ( !(data_valid == true) );

				// Read input data
				tmp_data = in_data.read();
				m_block_data[index] = tmp_data;
				// Remove signal request for data
				data_req.write(false);
				index++;

				while (data_valid == true) wait();

				wait();  
			}

			// Perform algo on block_data
			AlgoProcess();
			// ...................

#ifdef _ALGO_DEBUG
			cout << "Writing the transform values..." << endl;
#endif

			// Writes output data block
			index = 0; 
			while( index < ALGO_BLOCK_SIZE)
			{
				// Output data and signal ready
				tmp_data = m_block_data[index];
				out_data.write(tmp_data); 
				data_ready.write(true);
				
				// Wait for data received
				do { wait(); } while ( !(data_ack == true) );
				data_ready.write(false);
				index++;

				while (data_ack == true) wait();
				wait();
			}

#ifdef _ALGO_DEBUG
		cout << "Done..." << endl;
#endif

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

	// Check to clear peak
	int peak_clear = reg2 & CLEAR_PEAK_BIT;

	// Check enable iir filter
	int enable_iir = reg2 & ENABLE_IIR_BIT;

	// Read IIR coefficients
	m_coef0 = in_coef0.read();
	m_coef1 = in_coef1.read();
	m_coef2 = in_coef2.read();
	m_coef3 = in_coef3.read();
	m_coef4 = in_coef4.read();

	// Wait 1 clock cycle
	wait();
		
	for (short i = 0; i < ALGO_BLOCK_SIZE; i++)
	{
		// Mulitply gain on input sample 
		tmp_in = m_block_data[i] * in_gain;
		tmp_out = tmp_in;

		if (enable_iir == ENABLE_IIR_BIT)
		{
			// IIR filter (Biquad) y = b0*x + b1*x1 + b2*x2 - a0*y1 - a1*y2 
			tmp_out =   m_coef0 * tmp_in
					  + m_coef1 * m_x1
					  + m_coef2 * m_x2
				      - m_coef3 * m_y1
					  - m_coef4 * m_y2;

			// Wait 1 clock cycle
			wait();

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
		m_block_data[i] = tmp_out;

		// Calculate peak
		if (peak_clear == CLEAR_PEAK_BIT) 
		{
			m_peak = 0;
		}
		else
		{
			if (tmp_out < 0) 
				tmp_out *= -1; // Absolute value
			if (tmp_out > m_peak) 
				m_peak = tmp_out; // Set new peak
		}

		// Output  current peak
		out_reg2.write(m_peak);

		// Next clock cycle
		wait();
	}
}
