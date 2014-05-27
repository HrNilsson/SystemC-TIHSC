/*
 * KMeans.cpp
 *
 *  Created on: May 27, 2014
 *      Author: rene
 */

#include "KMeans.h"

#include "k_means.h"

void KMeans::RunKMeans() {

	k_means(image_output_local, texton_local);

}
