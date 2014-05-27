/*
 * CPU.h
 *
 *  Created on: May 27, 2014
 *      Author: rene
 */

#ifndef CPU_H_
#define CPU_H_

#include <systemc.h>
//#include "defs.h"


class CPU : public sc_module
{
	float im[96516];
	float* image_output_local;
	int* texton_local;

public:
	sc_signal<bool> readDone;
	sc_out<bool> filterDone;
	sc_in<bool> kMeansDone;

	void ReadImage();
	void WriteImage();
	void Filter();

	SC_HAS_PROCESS(CPU);

	CPU (sc_module_name nm, float* image, int* texton)
	: sc_module(nm)
	{
		image_output_local = image;
		texton_local = texton;

		SC_THREAD(ReadImage);
		
		SC_THREAD(WriteImage);
			dont_initialize();

		SC_THREAD(Filter);
			dont_initialize();
			sensitive << readDone.posedge_event();
	}
};


#endif /* CPU_H_ */
