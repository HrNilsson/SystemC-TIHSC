#ifndef MIXER_H_
#define MIXER_H_
//============================================================================
// Name        : Mixer.h
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector design using templates
// 				 This is an untimed model
//============================================================================
#include <systemc.h>

/**
 * Template Parameters:
 * 	class T - specifies the data-type used within the Mixer
 * 	T must be a numeric type that supports:
 * 		operator==(const T&)
 * 		operator=(int)
 * 		operator+=(const T&)
 * 		operator*(const T&)
 * 
 *  Constructor parameters:
 * 		sc_module_name name - specifies instance name
 * 		T gain - input gain
 **/

template <class T> 
class Mixer : public sc_module 
{
public:
	sc_port<sc_fifo_in_if<T>,0> in;
	sc_fifo_out<T> out;
	
	SC_HAS_PROCESS(Mixer);
	
	Mixer(sc_module_name name, 
		  T gain) :
		  sc_module(name),
		  m_gain(gain)
	{
		SC_THREAD(DoMix);
	}
	
private:
	T m_gain;
	
	void DoMix()
	{
		T sample;
		
		while (1)
		{
			sample = 0;
		    for (int i = 0; i < in.size(); i++) 
		    {
		    	sample += in[i]->read() * m_gain;
		    }
		    out.write(sample);
		}
	}
};

#endif /*MIXER_H_*/
