/*
 * 	Name: Cecilie Crone Rasmussen & Maiken Bjerg Møller
 * 	Project name: Texton filtering (exam project)
 * 	Course: Data-parallel computing Q1 2013
 */

#ifndef _K_MEANS_
#define _K_MEANS_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "filters.h"
#ifndef N_PIXELS
#define N_PIXELS 96516
#endif

#ifndef NUM_FILT
#define NUM_FILT 15
#endif

#define N_CLUSTERS 64
#define N_ITERATIONS 1000

#ifdef __cplusplus
extern "C" {
#endif

void k_means_init(float* centers, float* feature_image);

void k_means_calc_distance(float* centers, float* feature, int* pixelClusterIndex);

void calc_mean_value(int* labelImage, float* feature_image, float* means);

void k_means(float* features, int* textonmap);

#ifdef __cplusplus
}
#endif

#endif /* _K_MEANS_ */
