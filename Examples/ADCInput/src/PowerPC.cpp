//BEGIN PowerPC.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "PowerPC.h"
#include "ADCSource.h"

#define PER_DIV 1  // How fast to simulate reading buffer based on sample periode

PowerPC::PowerPC(sc_module_name nm)
: sc_module(nm)
{
    SC_THREAD(Simulate);
	sensitive << ready_in;
    dont_initialize();
}

void PowerPC::Simulate(void)
{
	while (1)
	{
		wait(SAMPLE_PERIODE, SC_NS);

		// Poll for data in buffer
		while (ready_in->read() == true)
		{
			// Read all data in buffer
			read_out->write(true);
			wait(1, SC_NS);// Wait for data to be ready
			cout << "Data : " << data_in->read() << ", ";
			wait(20, SC_NS);
			read_out->write(false);
			wait(20, SC_NS);
		}
		
		// Newline if buffer is empty
		cout << " ... \n";
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: PowerPC.cpp,v 1.2 2004/02/02 12:08:16 dcblack Exp $
