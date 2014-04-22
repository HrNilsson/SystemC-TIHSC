#ifndef OUTADAPTER_H_
#define OUTADAPTER_H_
//============================================================================
// Name        : OutAdapter.h
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector  design using templates
// 				 This is a timed model
//============================================================================
#include "Defs.h"

template <class T, unsigned N>
class OutAdapter: public sc_fifo_in_if <T >, public sc_module
{

  public:

	sc_in<bool> clock; // Clock
	sc_in<bool> reset; // Reset
	sc_in<bool> sample_clock; // Sample clock
	sc_in<sc_int<N> >  in_data; // Input port 

    void read(T & data)
    {
 		data = read(); 
    }
    
    T read()
    {
    	int idata;
    	double ddata;
    	T odata;
    	if (reset == false)
    	{
    		// Read sample data on posedge event
	    	wait(sample_clock.posedge_event());
			wait(clock.posedge_event());
			idata = in_data.read();
			ddata = fixed2float(idata);
			odata = (T)ddata;
			return (odata);
    	}

    	wait(clock.posedge_event());
    	return 0;
    }

    OutAdapter (sc_module_name name_)
    : sc_module (name_)
    {
    }

  private:

    bool nb_read(T & data)
    {
      SC_REPORT_FATAL("/OutAdapter", "Called nb_read()");
      return false;
    }

    virtual int num_available() const
    {
      SC_REPORT_FATAL("/OutAdapter", "Called num_free()");
      return 0;
    }

    virtual const sc_event& data_written_event() const
    {
      SC_REPORT_FATAL("/OutAdapter", "Called data_read_event()");
      return *new sc_event;
    }

};

#endif /*OUTADAPTER_H_*/
