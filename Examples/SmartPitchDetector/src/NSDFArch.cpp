//============================================================================
// Name        : NSFDArch.cpp
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector  design using templates
// 				 This is a timed model
//			     Calculates the normalized squared difference function
//============================================================================
#include "Defs.h"
#include "NSDFArch.h"

// Name of test files
const std::string nsdf_file("output_nsdf.txt");
const std::string acf_file("output_acf.txt");
const std::string sdf_file("output_sdf.txt");

void NSDFArch::DoCalculate()
{
	sc_int<ALGO_BITS> temp1;
	sc_int<ALGO_BITS> temp2;
	sc_int<ALGO_BITS> temp3;
	sc_int<ALGO_BITS> temp4;

	sc_int<ALGO_BITS*2> temp2d;
	sc_int<ALGO_BITS*2> temp3d;
	
	cout << "NSDFArch Started" << endl;

	ofstream *output_nsdf = new ofstream(nsdf_file.c_str());
	ofstream *output_acf = new ofstream(acf_file.c_str());
	ofstream *output_sdf = new ofstream(sdf_file.c_str());

	if (!output_nsdf)
	{
		cerr << "ERROR: Problem opening " << nsdf_file << " for output." << endl;
		return;
	}

	while(true)
	{			
		// Check if reset is active
		if (reset == true)
		{
			idx = 0;
		}
		else
		{				
			// Read new data sample
			sample = in_data.read();
			m_x[idx++] = sample;
			cout << idx << " Sample : " << sample << endl;
			out_data.write(sample);

			if (idx == WINDOW)
			{
				cout << " Calculating NSDF..." << endl;

				// Compute normalized squared difference function
				for (unsigned tau = 0; tau < WINDOW; tau++)
				{
					n_tau[tau] = m_x[tau];
					
					for (unsigned j = 0; j < WINDOW-1-tau; j++)
					{
						temp1 = r_tau[tau];
						temp2d = m_x[j]*m_x[j+tau];
						temp2 = temp2d >> ALGO_BITS;
						r_tau[tau] = temp1 + temp2; // ACF type II (2)

						temp1 = m_tau[tau];
						temp2d = m_x[j]*m_x[j];
						temp2 = temp2d >> ALGO_BITS;
						temp3d = m_x[j+tau]*m_x[j+tau];
						temp3 = temp3d >> ALGO_BITS;

						temp4 = temp1 + temp2;
						m_tau[tau] = temp4 + temp3; // SDF modified (6)

						// Back annotation from RTL timing analysis (Quartus)
						wait(29, SC_NS);
					}
				}
				for (unsigned tau = 0; tau < WINDOW; tau++)
				{
					temp1 = m_tau[tau];
					if ((int)temp1 == 0)
					{
						n_tau[tau] = 0;
						cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Arch tau zero" << endl;
					}
					else
					{
						cout << "ACF " << r_tau[tau] << " SDF "<< m_tau[tau] << endl;
						*output_acf << fixed2float(r_tau[tau]) << endl;
						*output_sdf << fixed2float(m_tau[tau]) << endl;

						temp2d = r_tau[tau] << ALGO_BITS-1;
						temp2 = m_tau[tau];
						temp3 = temp2d/temp2;
						n_tau[tau] = temp3 << 1; // Normalized NSDF (-1 to 1) (9)
					}

					// Back annotation from RTL timing analysis (Quartus)
					wait(162, SC_NS);

					// Output NSDF buffer (Unbounded FIFO buffer)
					sample = n_tau[tau];
					cout << "Tau : " << sample << endl;
					*output_nsdf << fixed2float(sample) << endl;
				}

				idx = 0;

				wait();
				wait();
				wait();

				// Stop simulation
				sc_stop();
			}
		}

		// Wait for next pos edge of sample clock
		wait();
	}
}
