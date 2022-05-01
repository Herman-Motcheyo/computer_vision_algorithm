#ifndef __CONTOUR_H
#define __CONTOUR_H

#include "./Convolution.h"

Image contour_with_sobel(Image m) ;

// la premiere derivee permet la detection des contours.
Image derive(Image m , int seuil);

#endif

