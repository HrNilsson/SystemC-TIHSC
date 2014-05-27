/*
 * KMeans.h
 *
 *  Created on: May 27, 2014
 *      Author: rene
 */

#ifndef KMEANS_H_
#define KMEANS_H_

#include <systemc.h>

class KMeans : public sc_module
{
	int* texton_local;
	float* image_output_local;

public:
	sc_in<bool> filterDone;
	sc_out<bool> kMeansDone;

	void RunKMeans();

	SC_HAS_PROCESS(KMeans);

	KMeans (sc_module_name nm, int* texton, float* image)
		: sc_module(nm)
	{
		image_output_local = image;
		texton_local = texton;

		SC_THREAD(RunKMeans);
			dont_initialize();
			sensitive << filterDone.posedge_event();

	}
};


#endif /* KMEANS_H_ */
