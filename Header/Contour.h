#ifndef __CONTOUR_H
#define __CONTOUR_H

#include "./Convolution.h"



// la premiere derivee permet la detection des contours.
Image derive(Image m , int seuil);
Image laplacien(Image derive , int seuil);

void contour(Image , char* type , int seuil);
void hough(Image , int theta , int rho ,int seuil);
void houghv2(Image m);
Image contour_with_sobel(Image m) ;
Image contour_with_Prewitt(Image m );
Image contour_with_Roberts(Image m);

#endif

