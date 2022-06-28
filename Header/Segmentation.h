#ifndef __SEGMENTATION_H
#define __SEGMENTATION_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "Image.h"
#include "../datastructure/header/LinkedList.h"

//mauvaise version de Kmeans
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


////////////////////////KMEANS//////////////////////////////////////
//permet d effectuer l'algorithme de kmeans
/*
   m : image à niveau de gris
   K : nombre de cluster
*/
Image kmeansOptimale(Image m, int K);

//Permet d'initialiser les clusters
List *initialiseCluster(int **M , int nbr_line , int nbr_col , struct Point **center_tab , int nbr_cluster , List garbage);

//Permet de verifier si les clusters sont stables c'est a dire d'une itération à l'autre tous ne change pas
boolean is_stable(const List *new_cluster_tab, const List *old_cluster_tab, int nbr_cluster);

//permet
List *reassignment(const List *cluster_tab, const struct Point **center_tab, int nbr_cluster) ;

//permet de determiner les points les plus proches d'un centre
int* point_proche_centre(const struct Point *point, const struct Point **center_tab, int nbr_cluster);

//permet de calculer la distance entre 2 points(Pixels)
float calculate_distance(const struct Point *point1, const struct Point *point2);

//Permet de calculer le nouveau centre du cluster
struct Point *calcul_centre(const List cluster);

//Permet de copier un ensemble de Points
List *copie_ensemble_cluster(const List *cluster_tab, int nbr_cluster);

//permet de copier un cluster
List copy_cluster(const List cluster);

struct Point *copy_point(const struct Point *point);

void free_cluster(List cluster);
void free_set_of_cluster(List *tab, int nbr_cluster);

//algorithme finale de Kmeans pour les images à niveaux de gris
Image kmeans_f_niveau_de_gris(Image image, int nbr_cluster);


int **kmf(int **d, int n_ligne, int n_col, int K, int min, int max, double e1, double e2);
#endif