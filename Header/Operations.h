#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Image.h"

int** generate_matrice(int nb_line,int nb_column);
struct Image read_Image_file(char *path);
void write_Image_to_file(  struct Image img , char *path );
struct Image transpose_Image(struct Image);

/*  Amelioration du contraste */
/* rappel herman :NB: min < max */

struct Image transformation_lineaire(struct Image , int max , int min);
struct Image transformation_saturation( struct  Image , int max , int min ,int smax , int smin);
struct Image egalisation_histogramme(Image);
int MAX_VALUE(int  ,int );
struct Image addition(struct Image , struct Image);
struct Image soustration(struct Image img1, struct Image img2);
struct Image multiplication(struct Image img1, float ratio);

struct Image Et(Image , Image);
struct Image OU(Image , Image);

#endif