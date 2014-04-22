#ifndef NSDFFunc_H_
#define NSDFFunc_H_
//============================================================================
// Name        : NSFDFunc.h
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

template <class T, unsigned W>
class NSDF : public sc_module
{
public:
	sc_fifo_in<T> in;
	sc_fifo_out<T> out;
	sc_fifo_out<T> acf;
	
	SC_HAS_PROCESS(NSDF);
	
	NSDF(sc_module_name name) :
		   sc_module(name)
	{
		sc_assert(W > 0);
		idx = 0;
		SC_THREAD(DoCalculate);
	}
	
private:
	unsigned idx;
	unsigned loop_cnt;
	T sample;
	T m_x[W]; 	// Window of input samples
	T r_tau[W]; // Autocorrelation ACF type II (ACF)
	T m_tau[W]; // Squared difference function modified SDF (SDF)
	T n_tau[W]; // Normalized squared difference function (NSDF)
	
	//std::cout << "NSDF functional simulation" << std::endl;

	void DoCalculate()
	{
		while(1)
		{			
			// Read new data sample
			sample = in.read();
			m_x[idx++] = sample;
			// Window size for computing NSDF 
			if (idx == W)
			{
				loop_cnt = 0;
				// Compute normalized squared difference function
				for (unsigned tau = 0; tau < W; tau++)
				{
					r_tau[tau] = 0;
					m_tau[tau] = 0;
					for (unsigned j = 0; j < W-1-tau; j++)
					{
						r_tau[tau] = r_tau[tau] + m_x[j]*m_x[j+tau]; // ACF type II (2)
						m_tau[tau] = m_tau[tau] + m_x[j]*m_x[j] + m_x[j+tau]*m_x[j+tau]; // SDF modified (6)
						loop_cnt++;

					}
				}
				for (unsigned tau = 0; tau < W; tau++)
				{
					if (m_tau[tau] == 0)
					{
						n_tau[tau] = 1;
						cout << "Tau zero" << endl;
					}
					else
						n_tau[tau] = 2*r_tau[tau]/m_tau[tau]; // Normalized NSDF (-1 to 1) (9)

					// Output NSDF buffer (Unbounded FIFO buffer)
					sample = n_tau[tau];
					//cout << sample << endl;
					out.write(sample);
					sample = r_tau[tau];
					acf.write(sample);		
				}
				idx = 0;
				cout << "Loop cnt: " << loop_cnt << endl;
			}
						
		}
	}
};

#endif /*NSDFFunc_H_*/
