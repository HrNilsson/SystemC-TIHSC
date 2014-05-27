/*
 * 	Name: Cecilie Crone Rasmussen & Maiken Bjerg Møller
 * 	Project name: Texton filtering (exam project)
 * 	Course: Data-parallel computing Q1 2013
 */

#include <math.h>
//#include "debugging.h"
#include "k_means.h"
#include <time.h>
#include <sys/time.h>


void k_means_init(float* centers, float* feature_image)
// float* centers are an array with the centers of 64 clusters in NUM_FILT dimensions.
{
  srand (time(NULL));
  int r;
  int c;
  int f;
  for(c = 0; c < N_CLUSTERS; c++)
  {
    r = rand() % N_PIXELS;
    
    for(f = 0; f < NUM_FILT; f++)
    {
      centers[c*NUM_FILT+f] = feature_image[r*NUM_FILT+f];
    }
  }
}

void k_means_calc_distance(float* centers, float* feature, int* pixelClusterIndex)
// float* centers are an array with the cenr_d,ters of 64 clusters in NUM_FILT dimensions.
// float* feature in a pointer to the featurearray with size N_PIXELS*NUM_FILT
// int* pixelClusterIndex is a pointer to an array of size N_PIXELS and holds the index of the nearest cluster (0-63)
{
  float* center = (float*)malloc(sizeof(float)*N_CLUSTERS*NUM_FILT);
  float* d = (float*)malloc(sizeof(float)*N_PIXELS);
  memset(d, 0, sizeof(float)*N_PIXELS);
  float temp_d = 0.0f;
  float min_d;
  int p,c,i;
  
  for(p = 0; p < N_PIXELS; p++)
  {
    // set min_d to maximum distance to evaluate new distances for every pixel
    min_d = 1000.0f;
    for(c = 0; c < N_CLUSTERS; c++)
    {
      for(i = 0; i < NUM_FILT; i++)
      {
	d[p] += pow(centers[c*NUM_FILT+i]-(double)(feature[p*NUM_FILT+i]),2);
      }
      temp_d = sqrt(d[p]);
      // Nulstil d[p]
      d[p] = 0.0f;
      // Find index for minimum distance to clusters per pixel
      if(temp_d < min_d)
      {
	pixelClusterIndex[p] = c;
	// min_d contains the minimum distance in current cluster
	min_d = temp_d;
      }
      else
      {
      }
    }
  }
  free(d);
}

void calc_mean_value(int* labelImage, float* feature_image, float* means)
// int* labelImage is a pointer to ... of size N_PIXELS
// float* feature_image is a pointer to the feature array of size N_PIXELS*NUM_FILT
// float* means is a pointer to the array where to write the updated centers from the mean value of points within a given cluster. Size of mean is N_CLUSTERS*NUM_FILT.
{
  int n_points;
  float* temp_m = (float*)malloc(sizeof(float)*NUM_FILT);
  int c,p,i,m;
  
  for(c = 0; c < N_CLUSTERS; c++)
  {
    n_points = 0;
    memset(temp_m, 0, sizeof(float)*NUM_FILT);
    for(p = 0; p < N_PIXELS; p++)
    {
      if(labelImage[p] == c)
      {
	for(i = 0; i < NUM_FILT; i++)
	{
	  temp_m[i] += feature_image[p*NUM_FILT+i];
	}
	  
	n_points++;
      }
    }
    
    if(n_points > 0)
    {
      for(m = 0; m < NUM_FILT; m++)
      {
	means[c*NUM_FILT+m] = temp_m[m]/(float)n_points;
      }
    }
  }
  free(temp_m);
}

void k_means(float* features, int* textonmap)
{
  float* center = (float*)malloc(sizeof(float)*N_CLUSTERS*NUM_FILT);
  int* result = (int*)malloc(sizeof(int)*N_PIXELS);
  float* meanValues = (float*)malloc(sizeof(float)*N_CLUSTERS*NUM_FILT);
  
  //clock_t t1, t2;
  //double diff;

  //timeval stop, start;
  //gettimeofday(&start, NULL);
  k_means_init(center, features);
  //gettimeofday(&stop, NULL);
  //printf("K-means init: %lu us.\n", (stop.tv_usec - start.tv_usec));
  int iterator;
  
  k_means_calc_distance(center, features, textonmap);
  
  calc_mean_value(textonmap, features, meanValues);

  //t1 = clock();
  for(iterator = 0; iterator < 1; iterator++)
  {
    k_means_calc_distance(meanValues, features, textonmap);
      
    calc_mean_value(textonmap, features, meanValues);
  }
  //t2 = clock();
  //diff = (((double)t2 - (double)t1) / CLOCKS_PER_SEC ) * 1000;   
  //printf("1000 iterations of k-means: %5.6f\n",diff); 
  
  free(center);
  free(result);
  free(meanValues);
}


