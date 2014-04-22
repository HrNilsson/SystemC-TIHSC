//----------------------------------------------------------------------------------------------
// CodecSink.cpp (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "CodecSink.h"

void CodecSink::entry()
{
	bool AudioSync_last = false;
	int tmp_out;
	sc_int<ALGO_BITS> tmp;
	FILE* fp_data;
	fp_left = fopen(OUTPUT_FILE_LEFT,"w");
	fp_right = fopen(OUTPUT_FILE_RIGHT,"w");

	cout << "CodecSink started" << endl;
	while(true)
	{ 
		// Wait for next AudioSync signal
		fp_data = 0;
		if (AudioSync == true && AudioSync_last == false)
			fp_data = fp_left;
		if (AudioSync == false && AudioSync_last == true)
			fp_data = fp_right;

		AudioSync_last = AudioSync;

		if (fp_data != 0)
		{
			// Read in data
			tmp = AudioOut.read();
			tmp_out = tmp;
#if 1
			fprintf(fp_data, "%d\n", tmp_out);
#else
			fprintf(fp_data, "%d  %8.0f\n", tmp_out, sc_time_stamp().to_double());
#endif
		}
		wait();
	}
}
