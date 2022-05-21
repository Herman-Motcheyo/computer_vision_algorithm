#ifndef __SEGMENTATION_H
#define __SEGMENTATION_H

#include "Image.h"

void mean_cluster();
void upate_center();
int Manathan(int* , int* , int ,int);
void kmeans(Image , int k , int min_inertia , int);

#endif