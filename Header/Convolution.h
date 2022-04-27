#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Operations.h"
//filtre passe bas
/*
Atténue le bruit et les détails
(basses fréquences) lissage
*/

int**  initialise_filtre(int);
float**  filtre_mean(int rayon);
float** filtre_gaussien(int rayon);
struct Image filter_with_median(struct Image  , int rayon);
struct Image filter_with_mean(struct Image  , int rayon);
struct Image filter_with_gaussian(struct Image  , int rayon);

#endif