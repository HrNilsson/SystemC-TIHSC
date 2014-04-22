//----------------------------------------------------------------------------------------------
// sink.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "defs.h"
#include "IIRFilter.h"

// Macro to wait a number of ms
#define WaitMs(ms) 	wait(CLK_PERIODE*200*ms, SC_NS)

// Macro to print log text
#define LogTxt(txt)	cout << "Time " << sc_time_stamp().to_double() << " " << txt << endl;

class user: public sc_module 
{
public:
	// Clock
	sc_in_clk CLK;   
	sc_out<bool> reset;

	sc_out<sc_int<WBUS> >  set_gain;  // Register Gain
	sc_out<sc_int<WBUS> >  set_user;  // User Register (Clear peak)
	sc_in<sc_int<WBUS> >   get_peak;  // Register Peak

	sc_out<sc_int<WBUS> >  set_coeff0;  // IIR Coefficients
	sc_out<sc_int<WBUS> >  set_coeff1;  // IIR Coefficients
	sc_out<sc_int<WBUS> >  set_coeff2;  // IIR Coefficients
	sc_out<sc_int<WBUS> >  set_coeff3;  // IIR Coefficients
	sc_out<sc_int<WBUS> >  set_coeff4;  // IIR Coefficients

private:
	IIRFilter IIR;

	void GainTest(int &loops);
	void SetCoefficients(void);
	void Entry(); 

public:
	SC_CTOR(user)
	{
		SC_THREAD(Entry);
		sensitive_pos << CLK;
		dont_initialize();
	}

};
