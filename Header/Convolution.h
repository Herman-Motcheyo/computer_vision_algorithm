#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Operations.h"

//filtre passe bas
/*
Atténue le bruit et les détails
(basses fréquences) lissage
*/

float **initialise_filtre(int);

float **filtre_mean(int rayon);
/*
Le filtre gausssien suit une loi gaussienne donc on a la loi de guass dans la boucle
 Il permet aussi le lissage de l'image et enleve les bruits.
*/
float **filtre_gaussien(int rayon, float ecart_type);

/*
 le filtre moyenneur permet : 
      le lissage de l image
      remplace chaque pixel par la moyenne de ces voisins
      reduit le bruit
      reduit les details non important
      brouille ou rend flou l image
*/
float **filtre_moyenneur(int rayon);

/*
 permet de faire de la convolution  
*/
int **convolveMult(int **m, float **filtre, int largeur, int longueur, int rayon, int MAX_PIXEL_VALUE);
Image convolution(Image, char *nom_filtre, int rayon);

//permet d'afficher le filtre
void printFilter(float** filtre , int rayon);

//Permet d'effactuer le tri et de retourner la valeur médiane dans un tableau
int findMedianWithBubbleSort(int* tab, int length);


struct Image filter_with_median(struct Image, int rayon);
struct Image filter_with_mean(struct Image, int rayon);
struct Image filter_with_gaussian(struct Image, int rayon);

//permet de liberer l'espace mémoire occupée par le filtre
void freeFilter(float** m,int n);

float** read_filter(char *path);
Image contour_filter(char *path , Image m  , int seuil);
Image contour_filtersansSeuil(char *path, Image m);

//permet d' effectuer la convolution à partir d'un filtre donné
Image convolution_filter_path(Image m ,  char* path_filter);


#endif