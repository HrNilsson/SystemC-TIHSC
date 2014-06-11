/*
 * 	Name: Cecilie Crone Rasmussen & Maiken Bjerg Møller
 * 	Project name: Texton filtering (exam project)
 * 	Course: Data-parallel computing Q1 2013
 */

#include "debugging.h"

void writeFloats2File(const char* filename, float* data, int dataLen)
{
	FILE* of = fopen(filename, "w");
	int i;
	for(i=0;i<dataLen;i++)
	{
		fprintf(of,"%f,\n", data[i]);
	}
	fclose(of);
}

void writeComplex2File(const char* filename, cufftComplex* data, int dataLen)
{
	FILE* of = fopen(filename, "w");
	int i;
	for(i=0;i<dataLen;i++)
	{
		fprintf(of,"%f+%fi,\n", data[i].x,data[i].y);
	}
	fclose(of);
}

void writeInts2File(const char* filename, int* data, int dataLen)
{
	FILE* of = fopen(filename, "w");
	int i;
	for(i=0;i<dataLen;i++)
	{
		fprintf(of,"%i,\n", data[i]);
	}
	fclose(of);
}

