#ifndef CIRBUFFER_H
#define CIRBUFFER_H
//BEGIN CirBuffer.h (systemc)
// Asynchronous input buffer with 4-128 samples of n bit width
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

#define MAX_SIZE	16						// Maximum buffer size (4,8,16,32,64,128, or 256 samples)
#define MAX_BITS	4						// Number of bits to count MAX_SIZE (2,3,4,5,6,7 or 8 bits)
#define SAMPLE_BITS 18						// Number of bits in sample

#ifdef _EA_IMPORT

class CirBuffer : public sc_module
{
public:

#else

SC_MODULE(CirBuffer) 
{

#endif

  // Input interface
  sc_in<sc_logic> busy_in;					// Logical high (1) when new din sample
  sc_in<sc_lv<SAMPLE_BITS> > data_in;		// Data input from ADC

  // Output interface
  sc_in<bool> read_in;						// Read stobe for data in buffer
  sc_out<bool> ready_out;					// Ready signal when data_out valid
  sc_out<sc_uint<SAMPLE_BITS> > data_out;	// Data ouput from buffer

  // Local data for circular buffer
  const unsigned int buf_size; 
  bool overflow;							// Set to 1 when buffer overflow
  sc_uint<MAX_BITS> in_ptr;					// Write input pointer
  sc_uint<MAX_BITS> out_ptr;				// Read output pointer
  sc_uint<MAX_BITS> len;					// Number of samples in buffer
  sc_uint<SAMPLE_BITS> buffer[MAX_SIZE];	// Circular buffer

  SC_CTOR(CirBuffer);
 
  // Triggered when busy_in goes high
  void SampleIn();

  // Triggered when busy_in goes low or read_in goes high
  void SampleOut();

};

#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: CirBuffer.h,v 1.2 2004/04/15 17:37:04 dcblack Exp $
