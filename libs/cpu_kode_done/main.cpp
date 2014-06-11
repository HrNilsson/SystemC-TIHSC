/*
 * 	Name: Cecilie Crone Rasmussen & Maiken Bjerg Møller
 * 	Project name: Texton filtering (exam project)
 * 	Course: Data-parallel computing Q1 2013
 */

#include "filtering.h"
#include "image2d.h"
#include "debugging.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char** argv) {
   
  // sti til input billede
  const char* input_file = "prikpige.raw";

  image2d* image = (image2d*)malloc(sizeof(image2d));
  image2d_init(image, WIDTH, HEIGHT, 1);
  image2d_load_from_raw(image, input_file);
      
  float im[N_PIXELS];
  int texton[N_PIXELS];
  
  // Konverter pixelsværdier til floats
  for(int i = 0; i < N_PIXELS; i++)
  {
    im[i] = ((float)(image->data[i]))/255.0;
  }
  
  //timeval stop, start;
  //gettimeofday(&start, NULL);
  
  clock_t t1, t2;
  double diff;
  
  t1 = clock();
  texton_filtering(im, texton);
  t2 = clock();
  diff = (((double)t2 - (double)t1) / CLOCKS_PER_SEC ) * 1000;   
  printf("Texton filtering: %5.6f\n",diff); 
  
  //gettimeofday(&stop, NULL);
  //printf("Texton filtering took: %lu s.\n", (stop.tv_sec - start.tv_sec));  
  
  writeInts2File("textonmap_cpu.txt", texton, N_PIXELS);
  
  image2d_free(image);
  return EXIT_SUCCESS;
}
