#ifndef __SEGMENTATION_H
#define __SEGMENTATION_H

#include "Image.h"


int Manathan(int* , int* , int ,int);
float *update_cluster(int **data, int n, int nbcolumn);
int length_cluster(int *points, int clusterId, int length_point);
void kmeans(Image , int k , int min_inertia , int);

#endif