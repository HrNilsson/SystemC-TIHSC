//----------------------------------------------------------------------------------------------
// main.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include "algo.h"
#include "top.h"

#if !defined(MODEL_SIM)

// Visual Studio version
int sc_main( int argc, char **argv)
{
	// Depricated since version SystemC version 2.2 is used
	//
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

#if defined(_MSC_VER)
	cout << "\n\tVisual Studio 8.0 - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

#if defined(__CYGWIN__)
	cout << "\n\tEclipse 3.3 and Cygwin - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

	// Instance of fft
	Top Top("AlgoTest");

	sc_start( 2000, SC_US );

	return 0;
}

#else

SC_MODULE_EXPORT(Top);

#endif
