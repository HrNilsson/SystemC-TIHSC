/*
 * 	Name: Cecilie Crone Rasmussen & Maiken Bjerg Møller
 * 	Project name: Texton filtering (exam project)
 * 	Course: Data-parallel computing Q1 2013
 */

#ifndef _DEBUGGING_
#define _DEBUGGING_

#include <stdlib.h>
#include <stdio.h>
#include <cufft.h>

#ifdef __cplusplus
extern "C" {
#endif
  
void writeFloats2File(const char* filename, float* data, int dataLen);

void writeComplex2File(const char* filename, cufftComplex* data, int dataLen);

void writeInts2File(const char* filename, int* data, int dataLen);

#ifdef __cplusplus
}
#endif

#endif /* _DEBUGGING_ */