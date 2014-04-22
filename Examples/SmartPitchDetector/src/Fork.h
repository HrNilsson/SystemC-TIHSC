#ifndef FORK_H_
#define FORK_H_
//============================================================================
// Name        : Fork.h
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector  design using templates
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
 **/

template <class T> 
class Fork : public sc_module 
{
public:
	sc_fifo_in<T> in;
	sc_port<sc_fifo_out_if<T>,0> out;
	
	SC_HAS_PROCESS(Fork);
	
	Fork(sc_module_name name) : sc_module(name)
	{
		SC_THREAD(DoFork);
	}
	
private:
	
	void DoFork()
	{
		T sample;
		
		while (1)
		{
			sample = in.read();
		    for (int i = 0; i < out.size(); i++) 
		    {
		    	out[i]->write(sample);
		    }
		}
	}
};

#endif /*FORK_H_*/
