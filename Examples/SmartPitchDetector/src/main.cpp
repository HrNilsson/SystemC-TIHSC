//============================================================================
// Name        : main.cpp
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector design using templates
//============================================================================
#include "Top.h"

int sc_main(int argc, char *argv[]) 
{
	// Depricated since version SystemC version 2.2 is used
	//
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	
	// Instance of Fir
	Top Top("SmartPitchDetector");
	
	sc_start();
	
	cout << "Test completed" << endl;
	return 0;
}
