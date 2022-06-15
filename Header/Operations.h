#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Image.h"
#include "Pixels.h"


struct Image read_Image_file(char *path);
void write_Image_to_file(  struct Image img , char *path );
struct Image transpose_Image(struct Image);

/*  Amelioration du contraste */
/* rappel herman :NB: min < max */

struct Image transformation_lineaire(struct Image );
struct Image transformation_saturation( struct  Image ,int smax , int smin);
struct Image transformation_morceau(struct Image , int smax , int smin);
struct Image transformation_morceau_inverse(struct Image , int smax , int smin);
struct Image transformation_gamma(Image  ,int c , float gamma);

struct Image egalisation_histogramme(Image);

int MAX_VALUE(int  ,int );
struct Image addition(struct Image , struct Image);
struct Image soustration(struct Image img1, struct Image img2);
struct Image multiplication(struct Image img1, float ratio);

Image binarisation(struct Image img , int seuil);
struct Image negatif_image(struct Image);
struct Image luminanceImage(struct Image);
struct Image contrasteImage(struct Image img);
//https://chowdera.com/2022/03/202203010744372381.html

int* histo(Image m);
void histogramme(Image m);
void write_Histogramme_to_File(int*);

int findMinPixelValueInM(Image m);
int findMaxPixelValueInM(Image m);

struct Image interpolationPlusProcheVoisin(struct Image img , int x , int y);
struct Image bilineaire(Image , int x , int y );

struct Image and(const Image , const Image);
struct Image or(const Image ,const Image);
struct Image xor(const Image ,const Image);

void saveHistogramme(int* , char*);
#endif