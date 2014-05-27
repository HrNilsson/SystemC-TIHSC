/*
 * 	Name: Cecilie Crone Rasmussen & Maiken Bjerg Møller
 * 	Project name: Texton filtering (exam project)
 * 	Course: Data-parallel computing Q1 2013
 */

#include "filtering.h"
#include "filters.h"
//#include "cuda_utilities.h"
//#include "debugging.h"
#include "k_means.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


void texton_filtering(float* image_input, int* texton)
{
 
   const float* filt[NUM_FILT] = {filter01, filter02, filter03, filter04, filter05, filter06, filter07, filter08, filter09, filter10, filter11, filter12, filter13, filter14, filter15};
   int i;
  //allocate space for zero padded image
  float* image_padded = (float*)malloc((WIDTH+(FILTERSIZE-1))*(HEIGHT+(FILTERSIZE-1))*sizeof(float));
  memset(image_padded, 0, (WIDTH+(FILTERSIZE-1))*(HEIGHT+(FILTERSIZE-1))*sizeof(float));
  float* image_output = (float*)malloc(sizeof(float)*N_PIXELS*NUM_FILT);
  
//   timeval stop, start;
//   gettimeofday(&start, NULL);
  //zero-pad image, so it is ready for convolution
  zeropad(image_input, image_padded, (FILTERSIZE-1)/2);
//   gettimeofday(&stop, NULL);
//   printf("zeropadding took: %lu us.\n", (stop.tv_usec - start.tv_usec));  
  
  //do this for all 15 filters
  for(i = 0; i < NUM_FILT; i++)
  {
    conv(filt[i], image_padded, image_output, i);
  }  
  
  
  k_means(image_output, texton);
  
}

// Foldningsfunktion, der tager et zeropadded billede ind og returnerer et klippet billede.
void conv(const float* filt, float* im, float* result, int nFilt)
{
  int step = (FILTERSIZE-1)/2;
  int pos = 0;	// Position i billede im
  int i, j, rPos;
  int h = HEIGHT+(FILTERSIZE-1);
  int w = WIDTH+(FILTERSIZE-1);
  float* temp_im_in = (float*)malloc(sizeof(float)*w*h);
  float* temp_im_out = (float*)malloc(sizeof(float)*N_PIXELS);
  int k;

  for(i = 0; i < (h*w); i++)
  {
    if(i >= step*w && i <= h*w-step*w && i%w >= step && i%w <= w-step )
    {
      // Inner loop - filtermasken
      for(j = 0; j < FILTERLEN; j++)
      {
	pos = i-step-(step*w)+j%FILTERSIZE+(w*(int)(j/FILTERSIZE));
	temp_im_in[i] += im[pos]*filt[j];    
      } 
    }
  }
  // Klip billede til
  cut_frame(temp_im_in, temp_im_out, step); 
  
  for(k = 0; k < N_PIXELS; k++)
  {
    rPos = k*NUM_FILT+nFilt;
    result[rPos] = temp_im_out[k];
  }
}

// zeropad funktion
void zeropad(float* im, float* im_out, int frame)
{    
  int pos;
  int m;
  int n;
  for(m = 0; m < HEIGHT; m++)
  {
    for(n = 0; n < WIDTH; n++)
    {
      pos = (frame+m)*(WIDTH+48) + n + frame;
      im_out[pos] = im[m*WIDTH+n];
    }
  }
}

// Denne funktion klipper rammen af et zeropaddad billede
void cut_frame(float* im_in, float* im_out, int frame)
{
  int pos = 0;
  int m;
  int n;
  for(m = 0; m < HEIGHT; m++)
  {
    for(n = 0; n < WIDTH; n++)
    {
      pos = (frame+m)*(WIDTH+48) + n + frame;
      im_out[m*WIDTH+n] = im_in[pos];
    }
  }
}







