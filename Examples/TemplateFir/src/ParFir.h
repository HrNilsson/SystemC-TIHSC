#ifndef PARFIR_H_
#define PARFIR_H_
//============================================================================
// Name        : ParFir.h
// Author      : Kim Bjerge
// Version     : 22. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized FIR filter design using templates
// 				 This is an untimed model
//============================================================================
#define SC_INCLUDE_FX
#include <systemc.h>
#include <math.h>

/**
 * Template Parameters:
 * 	class T - specifies the data-type used within the FIR
 * 	T must be a numeric type that supports:
 * 		operator==(const T&)
 * 		operator=(int)
 * 		operator+=(const T&)
 * 		operator*(const T&)
 * 	unsigned N - specifies the number of taps in FIR
 * 		N must be greater than zero
 * 
 *  Constructor parameters:
 * 		sc_module_name name - specifies instance name
 * 		const T* coeffs - pointer to coefficients array
 * 		coeffs array must contain N coefficients
 **/

template <class T, unsigned N>
class ParFir : public sc_module
{
public:
	sc_fifo_in<T> in;
	sc_fifo_out<T> out;
	
	SC_HAS_PROCESS(ParFir);
	
	ParFir(sc_module_name name, 
		   const double* coeffs) :
		   sc_module(name)
	{
		sc_assert(N > 0);
	
		for (unsigned i=0; i < N; i++)
		{
			m_delay_line[i] = 0;
			m_coeffs[i] = coeffs[i];
		}
		
		SC_THREAD(DoCalculate);
	}
	
private:
	T m_delay_line[N];
	T m_coeffs[N];
	
	void DoCalculate()
	{
		while(1)
		{
			// Shift samples within delay line
			for (int j = N-1; j > 0; j--)
				m_delay_line[j] = m_delay_line[j-1];
			
			// Read new data sample
			m_delay_line[0] = in.read();
			
			// Compute fir output
			T sum = 0;
			for (unsigned i=0; i < N; i++)
				sum += m_delay_line[i] * m_coeffs[i];
			
			out.write(sum);
		}
	}
};

/**
 * Abstract template interface class for FirCoefficients
 */
template <class T>
class FirCoeff_if
{
public:
	virtual const T *GetCoeffs(void) = 0;
	virtual T GetCoeff(int i) = 0;
	virtual int GetCoeffInt(int i) = 0;
};

/**
 * Template Parameters:
 * 	class T - specifies the data-type used within the LowPassFir
 * 	T must be a numeric type that supports:
 * 		operator==(const T&)
 * 		operator=(int)
 * 		operator+=(const T&)
 * 		operator*(const T&)
 * 	unsigned N - specifies the number of taps in FIR
 * 		N must be greater than zero and odd
 * 
 *  Constructor parameters:
 **/

template <class T, unsigned N>
class LowPassFir : public FirCoeff_if<T>
{
	
public:
	LowPassFir(int fs, int fa) : m_fs(fs), m_fa(fa)
	{
		assert(N > 0);
		assert(N%2 == 1); // Accept only odd number of coefficients
		
		// Digital FIR-filter calculation according to (8.33) Digital Signal Behandling, Erik Hüche
		int M = (N - 1)/2;
		for (int i = 0; i <= M; i++)
		{
			int m = M - i;
			coeff[i] = sin(2 * M_PI * m * (m_fa/m_fs)) / (m * M_PI);  
			coeff[M + m] = coeff[i];
		}
		coeff[M] = 2 * m_fa/m_fs; // (8.34)
	}
	
	virtual const T *GetCoeffs(void) 
	{ 
		return &coeff[0]; 
	}

	virtual T GetCoeff(int i) 
	{ 
		return coeff[i]; 
	}
	
	virtual int GetCoeffInt(int i)
	{
		double coeff = GetCoeff(i);
		int val = float2fixed(coeff);
		return val;
	};

private:
	T m_fs;
	T m_fa;
	T coeff[N];
};

/**
 * Template Parameters:
 * 	class T - specifies the data-type used within the HighPassFir
 * 	T must be a numeric type that supports:
 * 		operator==(const T&)
 * 		operator=(int)
 * 		operator+=(const T&)
 * 		operator*(const T&)
 * 	unsigned N - specifies the number of taps in FIR
 * 		N must be greater than zero and odd
 * 
 *  Constructor parameters:
 **/

template <class T, unsigned N>
class HighPassFir : public FirCoeff_if<T>
{
	
public:
	HighPassFir(int fs, int fa) : m_fs(fs), m_fa(fa)
	{
		assert(N > 0);
		assert(N%2 == 1); // Accept only odd number of coefficients
		
		// Digital FIR-filter calculation according to (8.35) Digital Signal Behandling, Erik Hüche
		int M = (N - 1)/2;
		for (int i = 0; i <= M; i++)
		{
			int m = M - i;
			coeff[i] = ( sin(m * M_PI) - sin(2 * M_PI * m * (m_fa/m_fs)) ) / (m * M_PI);  
			coeff[M + m] = coeff[i];
		}
		coeff[M] = 1 - 2 * m_fa/m_fs; // (8.36)
	}
	
	virtual const T *GetCoeffs(void) 
	{ 
		return &coeff[0]; 
	}

	virtual T GetCoeff(int i) 
	{ 
		return coeff[i]; 
	}
	
	virtual int GetCoeffInt(int i)
	{
		double coeff = GetCoeff(i);
		int val = float2fixed(coeff);
		return val;
	};

private:
	T m_fs;
	T m_fa;
	T coeff[N];
};

#endif /*PARFIR_H_*/
