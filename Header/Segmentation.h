#ifndef __SEGMENTATION_H
#define __SEGMENTATION_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "Image.h"
#include "../datastructure/header/LinkedList.h"

int Manathan(int* , int* , int ,int);
double distance(int *tab, float *T, int n);
float *update_cluster(int **data, int n, int nbcolumn , float* cluster);
int length_cluster(int *points, int clusterId, int length_point);
//float** initialize_cluster(Image m , int k );
float* int_to_float(int* t , int k);
void kmeans(Image , int k , int min_inertia , int);

/****************** ALGORITHME DE OTSU *************/
// algorithme de otsu version du support de cours
int otsu_version_du_support_du_cours(int* hist , int largeur , int longueur);

//permet de faire un seuillage avec l'algorithme de otsu
Image seuillageAutomatique(Image m);

//permet  d'effectuer le balayage des seuilles à gauche et droite
double computeOtsu(int *hist, int min, int max, int hauteur, int largeur);

//permet d'effectuer l'algorithme de otsu et determiner le bon seuil
int otsu(int hauteur, int largeur, Image img);

void otsufINALE(Image img);

/********* CROISSANCE DES REGIONS*************/

//permet de copier une matrice dans un autre
int** copy_matrix(int** mat , int largeur , int hauteur);

//permet d'executer l'algorithme de la croissance des regions
Image croissance_des_regions(Image image, int nombre_de_germe, int seuil);

//permet de disperser les germes
List dispersion_des_germes(struct Point *point, Image image, int seuil);

//permet de trouver les bon voisin
List bon_voisin(Image image, struct Point *point, int seuil);


#endif