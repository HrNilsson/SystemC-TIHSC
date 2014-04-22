#ifndef SOURCE_H_
#define SOURCE_H_
//============================================================================
// Name        : Source.cpp
// Author      : Kim Bjerge
// Version     : 22. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized FIR filter design using templates
// 				 This is an untimed model
//============================================================================

/**
 * Template Parameters:
 * 	class T - specifies the data-type used within the Source
 * 	T must be a numeric type that supports:
 * 		operator==(const T&)
 * 		operator=(int)
 * 		operator+=(const T&)
 * 		operator*(const T&)
 * 
 *  Constructor parameters:
 * 		sc_module_name name - specifies instance name
 * 		unsigned samples - number of samples to generate
 * 		unsigned fo - frequence of test signal
 **/
#include <math.h>
#include <systemc.h>


template <class T> 
class Source : public sc_module
{
public:
	sc_fifo_out<T> out;
	
	SC_HAS_PROCESS(Source);
	
	Source(sc_module_name name, 
			int samples, 
			int fo,
			int fs) : 
		sc_module(name),
		m_samples(samples),
		m_fo(fo),
		m_fs(fs)
	{
		SC_THREAD(DoStimuli);
	}
	
private:
	int m_samples;
	int m_fo;
	int m_fs;
	
	T Sine(int n)
	{
		return sin((2*M_PI/m_fs)*m_fo*n);
	}
	
	void DoStimuli()
	{
		T sample;
		
		if (m_samples < 0)
		{
			int n = 0;
			// Simulate forever
			while (1)
			{
				sample = Sine(n++);
				out.write(sample);			
			}
		}
		
		// Simulate for N samples
		for (int n = 0; n < m_samples; n++)
		{
			sample = Sine(n);
			out.write(sample);
		}	
		
	}
		
};

#endif /*SOURCE_H_*/
