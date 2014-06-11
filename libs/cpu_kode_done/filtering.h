/*
 * 	Name: Cecilie Crone Rasmussen & Maiken Bjerg Møller
 * 	Project name: Texton filtering (exam project)
 * 	Course: Data-parallel computing Q1 2013
 */

#ifndef _TEXTON_FILTERING_
#define _TEXTON_FILTERING_

#include "image2d.h"
#include "filters.h"
#include "k_means.h"
#include "debugging.h"

#ifdef __cplusplus
extern "C" {
#endif

void texton_filtering(float* image_input, int* texton);

void zeropad(float* im, float* im_out, int frame);

void conv(const float* filt, float* im, float* result, int nFilt);

void cut_frame(float* im_in, float* im_out, int frame);

#ifdef __cplusplus
}
#endif

#endif /* _TEXTON_FILTERING_ */