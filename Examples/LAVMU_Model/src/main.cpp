//----------------------------------------------------------------------------------------------
// main.cpp (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
#include "Algo.h"
#include "top.h"

int sc_main( int argc, char **argv)
{
	// Depricated since version SystemC version 2.2 is used
	//
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	cout << "Start" << endl;

#if defined(_MSC_VER)
	cout << "\n\tVisual Studio 8.0 - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

#if defined(__CYGWIN__)
	std::cout << "\n\tEclipse 3.3 and Cygwin - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

	// Instance of fft
	Top Top("LAVMU_Model");

	sc_start( 50000, SC_US );

	return 0;
}
