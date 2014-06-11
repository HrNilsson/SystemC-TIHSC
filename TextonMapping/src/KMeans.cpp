/*
 * KMeans.cpp
 *
 *  Created on: May 27, 2014
 *      Author: rene
 */

#include "KMeans.h"
#include "k_means.h"

void KMeans::RunKMeans() {
	using namespace std;
	cout << "kMeans starting" << endl;
	k_means(image_output_local, texton_local);


	cout << "Notify kMeans Done" << endl;
	kMeansDone.write(true);
}
