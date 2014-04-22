#ifndef INADAPTER_H_
#define INADAPTER_H_
//============================================================================
// Name        : InAdapter.h
// Author      : Kim Bjerge
// Version     : 25. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized FIR filter design using templates
// 				 This is a timed model
//============================================================================
#include "Defs.h"

template <class T, unsigned N>
class InAdapter: public sc_fifo_out_if <T >, public sc_module
{

  public:

	sc_in<bool> clock; // Clock
	sc_in<bool> reset; // Reset
	sc_in<bool> sample_clock; // Sample clock
	sc_out<sc_int<N> >  out_data; // Output port 

    void write (const T & data)
    {
    	double ddata;
    	int idata;
    	if (reset == false)
    	{
    		// Output sample data on negative edge of clock
	    	wait(sample_clock.negedge_event());
			wait(clock.posedge_event());
			ddata = (double)data;
			idata = float2fixed(ddata); 
			out_data.write(idata); 
    	}
    	else wait(clock.posedge_event());
    }

    InAdapter (sc_module_name name_)
    : sc_module (name_)
    {
    }

  private:

    bool nb_write( const T & data)
    {
      SC_REPORT_FATAL("/InAdapter", "Called nb_write()");
      return false;
    }

    virtual int num_free() const
    {
      SC_REPORT_FATAL("/InAdapter", "Called num_free()");
      return 0;
    }

    virtual const sc_event& data_read_event() const
    {
      SC_REPORT_FATAL("/InAdapter", "Called data_read_event()");
      return *new sc_event;
    }

};

#endif /*INADAPTER_H_*/
