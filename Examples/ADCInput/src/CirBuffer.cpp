//BEGIN CirBuffer.cpp (systemc)
// Asynchronous input buffer with 4-128 samples of n bit width
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "CirBuffer.h"

CirBuffer::CirBuffer(sc_module_name nm)
: sc_module(nm),
	buf_size(MAX_SIZE)
{
	// Set pointers and clear first element in buffer
	in_ptr = 0;
	out_ptr = 0;
	len = 0;
	buffer[0] = 0;
	overflow = false;

	// Register processes
    SC_METHOD(SampleIn);
    sensitive << busy_in.pos();	
    dont_initialize();

	SC_METHOD(SampleOut);
    sensitive << busy_in.neg();	
    sensitive << read_in.pos();	
    dont_initialize();
}

void CirBuffer::SampleIn(void) 
{
	buffer[in_ptr] = data_in->read();
	in_ptr += 1;
	if (len != buf_size-1) len += 1; // Increment samples in buffer
	else
	{
		overflow = true; // Signal overflow
		cout << ">>> Buffer overflow <<<\n\n";
	}
}

void CirBuffer::SampleOut(void) 
{	
	if (len > 0)
	{	
		// Signal data in buffer
		ready_out->write(true);
		
		// Read requested
		if (read_in.read() == true)
		{
			// Output next data in buffer 
			data_out->write(buffer[out_ptr]);
			
			// If more data in buffer increment pointer
			out_ptr += 1;
			len -= 1; // Decrement number of samples in buffer
			
			if (overflow == true) overflow = false; // Make overflow stiky
		}
	}

	// Signal no more data in buffer
	if (len == 0) ready_out->write(false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: CirBuffer.cpp,v 1.2 2004/02/02 12:08:16 dcblack Exp $
