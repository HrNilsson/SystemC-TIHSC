//----------------------------------------------------------------------------------------------
// Debounce.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Debounce button input detector to prevent "meta stability"

#include "Debounce.h"


void Debounce::Process()
{
	fQ1 = input;

	fQ2 = fQ1;

	fQ3 = fQ2;

	fCE4 = fQ2 ^ fQ3;

	if (fCE4.read() == SC_LOGIC_1) output = fQ2;

}

