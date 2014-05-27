/*
 * CPU.cpp
 *
 *  Created on: May 27, 2014
 *      Author: rene
 */

#include "CPU.h"
#include "image2d.h"
#include "filtering.h"
#include "filters.h"

void CPU::ReadImage() {

	 // sti til input billede
	  const char* input_file = "prikpige.raw";

	  image2d* image = (image2d*)malloc(sizeof(image2d));
	  image2d_init(image, WIDTH, HEIGHT, 1);
	  image2d_load_from_raw(image, input_file);


	  int texton[N_PIXELS];

	  // Konverter pixelsværdier til floats
	  for(int i = 0; i < N_PIXELS; i++)
	  {
	    im[i] = ((float)(image->data[i]))/255.0;
	  }

	  //wait(SC_NS)
	  readDone.write(true);

}


void CPU::WriteImage() {
	FILE* of = fopen("textonmap_cpu.txt", "w");
	int i;
	for(i=0;i<96516;i++)
	{
		fprintf(of,"%i,\n", texton_local[i]);
	}
	fclose(of);

}


void CPU::Filter() {
	   const float* filt[NUM_FILT] = {filter01, filter02, filter03, filter04, filter05, filter06, filter07, filter08, filter09, filter10, filter11, filter12, filter13, filter14, filter15};

	  //allocate space for zero padded image
	  float* image_padded = (float*)malloc((WIDTH+(FILTERSIZE-1))*(HEIGHT+(FILTERSIZE-1))*sizeof(float));
	  memset(image_padded, 0, (WIDTH+(FILTERSIZE-1))*(HEIGHT+(FILTERSIZE-1))*sizeof(float));
	  float* image_output = (float*)malloc(sizeof(float)*N_PIXELS*NUM_FILT);

	//   timeval stop, start;
	//   gettimeofday(&start, NULL);
	  //zero-pad image, so it is ready for convolution

	  	  zeropad(im, image_padded, (FILTERSIZE-1)/2);

	//   gettimeofday(&stop, NULL);
	//   printf("zeropadding took: %lu us.\n", (stop.tv_usec - start.tv_usec));

	  //do this for all 15 filters
	  for(int i = 0; i < NUM_FILT; i++)
	  {
	    conv(filt[i], image_padded, image_output, i);
	  }
	  image_output_local = image_output;

	  filterDone.write(true);
}
