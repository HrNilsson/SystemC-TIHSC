//----------------------------------------------------------------------------------------------
// sink.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "sink.h"

void sink::entry()
{
	sc_int<ALGO_BITS> tmp;
	int tmp_out;
	fp_data = fopen(OUTPUT_FILE_A,"w");

	data_ack.write(false);

	while(true)
	{ 
		// Wait for data ready
		do { wait(); } while ( !(data_ready == true) );

		// Read in data
		tmp = in_data.read();
		tmp_out = tmp;
#if 1
		fprintf(fp_data, "%d\n", tmp_out);
#else
		fprintf(fp_data, "%d  %8.0f\n", tmp_out, sc_time_stamp().to_double());
#endif
		data_ack.write(true);

		// Wait for data not ready
		do { wait(); } while ( !(data_ready == false) );
		
		wait();
		wait();
		wait();

		data_ack.write(false); 
	}
}
