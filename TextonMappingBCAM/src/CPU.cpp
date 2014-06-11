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

	  image2d* imageIn = (image2d*)malloc(sizeof(image2d));
	  image2d_init(imageIn, WIDTH, HEIGHT, 1);
	  image2d_load_from_raw(imageIn, input_file);

	  // Konverter pixelsværdier til floats
	  for(int i = 0; i < N_PIXELS; i++)
	  {
		  image[i] = ((float)(imageIn->data[i]))/255.0;
	  }

	  //wait(SC_NS)
	  using namespace std;
	  cout << "Notify Read Done" << endl;
	  readDone.notify();

}


void CPU::WriteImage() {
	using namespace std;
	cout << "Write starting" << endl;
	FILE* of = fopen("textonmap_cpu.txt", "w");
	int i;
	for(i=0;i<96516;i++)
	{
		fprintf(of,"%i,\n", texton[i]);
	}
	fclose(of);

	using namespace std;
  cout << "Writing File Done" << endl;

}


void CPU::Filter() {
	   const float* filt[NUM_FILT] = {filter01, filter02, filter03, filter04, filter05, filter06, filter07, filter08, filter09, filter10, filter11, filter12, filter13, filter14, filter15};

	  //allocate space for zero padded image
	  float* image_padded = (float*)malloc((WIDTH+(FILTERSIZE-1))*(HEIGHT+(FILTERSIZE-1))*sizeof(float));
	  memset(image_padded, 0, (WIDTH+(FILTERSIZE-1))*(HEIGHT+(FILTERSIZE-1))*sizeof(float));
	  //float* image_output = (float*)malloc(sizeof(float)*N_PIXELS*NUM_FILT);
	  using namespace std;
	  cout << "Filtering starting" << endl;
	//   timeval stop, start;
	//   gettimeofday(&start, NULL);
	  //zero-pad image, so it is ready for convolution

	  	  zeropad(image, image_padded, (FILTERSIZE-1)/2);

	//   gettimeofday(&stop, NULL);
	//   printf("zeropadding took: %lu us.\n", (stop.tv_usec - start.tv_usec));

	  //do this for all 15 filters
	  for(int i = 0; i < NUM_FILT; i++)
	  {
	    conv(filt[i], image_padded, imageFiltered, i);
	  }

	  using namespace std;
	  cout << "Notify Filter Done" << endl;

	  imageFilteredSig.write(imageFiltered);
	  textonSig.write(texton);
}
