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


public:
	sc_in<float*> imageFilteredSig;
	sc_in<int*> textonSig;
	sc_out<bool> kMeansDone;

	void RunKMeans();

	SC_HAS_PROCESS(KMeans);

	KMeans (sc_module_name nm)
		: sc_module(nm)
	{
		SC_THREAD(RunKMeans);
			dont_initialize();
			sensitive << textonSig;

	}
};


#endif /* KMEANS_H_ */
