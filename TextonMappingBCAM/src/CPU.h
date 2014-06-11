/*
 * CPU.h
 *
 *  Created on: May 27, 2014
 *      Author: rene
 */

#ifndef CPU_H_
#define CPU_H_

#include <systemc.h>


class CPU : public sc_module
{
	float image[96516] = {};
	float imageFiltered[96516*15] = {};
	int texton[96516] = {};


public:
	sc_out<float*> imageFilteredSig;
	sc_out<int*> textonSig;
	sc_in<bool> kMeansDone;
	sc_event readDone;

	void ReadImage();
	void WriteImage();
	void Filter();

	SC_HAS_PROCESS(CPU);

	CPU (sc_module_name nm)
	: sc_module(nm)
	{
		SC_THREAD(ReadImage);
		
		SC_THREAD(WriteImage);
			dont_initialize();
			sensitive << kMeansDone;

		SC_THREAD(Filter);
			dont_initialize();
			sensitive << readDone;
	}
};


#endif /* CPU_H_ */
