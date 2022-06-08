#ifndef __SEGMENTATION_H
#define __SEGMENTATION_H

#include "Image.h"


int Manathan(int* , int* , int ,int);
double distance(int *tab, float *T, int n);
float *update_cluster(int **data, int n, int nbcolumn , float* cluster);
int length_cluster(int *points, int clusterId, int length_point);
float** initialize_cluster(Image m , int k );
float* int_to_float(int* t , int k);
void kmeans(Image , int k , int min_inertia , int);

#endif