//----------------------------------------------------------------------------------------------
// source.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "source.h"

void source::entry()
{ 
	FILE *fp_data;
	int tmp_val;
	fp_data = fopen(INPUT_FILE_A, "r");

	data_valid.write(false);

	while(true)
	{ 
		// Wait for algo to request for data
		do { wait(); } while ( !(data_req == true) );

		// Read simulation input data from file
		if (fscanf(fp_data, "%d", &tmp_val) == EOF)
		{ 
			cout << "End of Input Stream: Simulation Stops" << endl;
			sc_stop();
			break;
		};

		out_data.write(tmp_val);

		// Signal to algo that data is ready
		data_valid.write(true);


		// Wait for stop data request 
		do { wait(); } while ( !(data_req == false) );
		
		wait();
		wait();
		wait();

		data_valid.write(false);

		wait();
	}
}
