#ifndef __FOURIER__
#define __FOURIER__

#include "./Image.h"

int **M_Imaginaire(Image m);
Image norme_f(int **imR , int**imI , int largeur , int hauteur);
Image phase(int **imR , int**imI , int largeur , int hauteur);
#endif